#include "codec.h"
#include "indexDict.h"
#include "task.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Mutex.h"
#include "muduo/net/TcpServer.h"
#include "muduo/net/EventLoop.h"
#include <boost/regex.hpp>

#include <json/json.h>
#include <stdio.h>
#include <set>
#include <unistd.h>

using namespace muduo::net;
using namespace muduo;

//全局单例对象
IndexDict* dict = IndexDict::getInstance();

class CorrectionServer
{
public:
	CorrectionServer(EventLoop* loop, const InetAddress& listenAddr)
	: _server(loop, listenAddr, "CorrectionServer")
	, _codec(std::bind(&CorrectionServer::onStringMessage, this, _1, _2, _3))
	{
		_server.setConnectionCallback(std::bind(&CorrectionServer::onConnection, this, _1));
		_server.setMessageCallback(std::bind(&LengthHeaderCodec::onMessage, &_codec, _1, _2, _3));
	}

	void start()
	{
		_server.start();
	}
private:
	void onConnection(const TcpConnectionPtr& conn);
	void onStringMessage(const TcpConnectionPtr& conn, const string& message, Timestamp);
private:
	typedef std::set<TcpConnectionPtr> Connections;
	TcpServer _server;
	LengthHeaderCodec _codec;
	Connections _connections;//用于保存所有连接的客户端
	Task _myTask;
};

void CorrectionServer::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << conn->localAddress().toIpPort() << " -> " << conn->peerAddress().toIpPort() << " is "
			 << (conn->connected() ? "UP" : "DOWN");
	if(conn->connected())
	{
		_connections.insert(conn);//每次监听fd有新连接到来是就会设置connected()为真，然后调用这个函数, 
								//此时我们把这个连接fd对应的TcpConnection对应的对象注册到_connections中。
	}
	else
	{
		_connections.erase(conn);//当一个连接断开之后也会调用这个回调函数,并且此时connected()为假，
								//所以在_connections中删除这个对象。
	}
}

void CorrectionServer::onStringMessage(const TcpConnectionPtr& conn, const string& message, Timestamp)
{
	string src_message = message;
	boost::regex reg("[^a-z]");
	string des_message = boost::regex_replace(src_message, reg, "");

	string result = _myTask.search(des_message);

	Json::Value root;
	root["des_string"] = Json::Value(result);
	root["src_string"] = Json::Value(message);
	Json::StyledWriter sw;
	string news = sw.write(root);

	_codec.send(conn, news);
}

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
	if(argc > 1)
	{
		EventLoop loop;
		unsigned short port = static_cast<unsigned short>(atoi(argv[1]));
		InetAddress serverAddr(port);

		CorrectionServer server(&loop, serverAddr);
		server.start();
		loop.loop();
	}
	else
	{
		printf("Usage: %s port\n", argv[0]);	
	}
}

