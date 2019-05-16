#include "codec.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Mutex.h"
#include "muduo/net/EventLoopThread.h"
#include "muduo/net/TcpClient.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace muduo;
using namespace muduo::net;


class CorrectionClient
{
public:
	CorrectionClient(EventLoop* loop, const InetAddress& serverAddr)
	: _client(loop, serverAddr, "CorrectionClient")
	, _codec(std::bind(&CorrectionClient::toStringMessage, this, _1, _2, _3))
	{
		_client.setConnectionCallback(std::bind(&CorrectionClient::onConnection, this, _1));
		_client.setMessageCallback(std::bind(&LengthHeaderCodec::onMessage, &_codec, _1, _2, _3));
		_client.enableRetry();
	}

	void connect()
	{
		_client.connect();
	}
	void disconnect()
	{
		_client.disconnect();
	}
	void write(const StringPiece& message)
	{
		MutexLockGuard lock(_mutex);
		if(_connection)
		{
			_codec.send(_connection, message);
		}
	}
private:
	//这两个函数都是由EventLoop线程回调的
	void onConnection(const TcpConnectionPtr& conn);
	void toStringMessage(const TcpConnectionPtr&, const string& message, Timestamp);
private:
	TcpClient _client;
	LengthHeaderCodec _codec;
	MutexLock _mutex;
	TcpConnectionPtr _connection GUARDED_BY(_mutex);
};

void CorrectionClient::onConnection(const TcpConnectionPtr& conn)
{
	LOG_INFO << conn->localAddress().toIpPort() << " -> "
             << conn->peerAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");
	MutexLockGuard lock(_mutex);
	if(conn->connected())
	{
		_connection = conn;
	}
	else
	{
		_connection.reset();
	}
}

void CorrectionClient::toStringMessage(const TcpConnectionPtr&, const string& message, Timestamp)
{
	printf("%s", message.c_str());
}

int main(int argc, char* argv[])
{
	LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
	if(argc > 2)
	{
		EventLoopThread loopThread;
		unsigned short int port = static_cast<unsigned short int>(atoi(argv[2]));
		InetAddress serverAddr(argv[1], port);

		CorrectionClient client(loopThread.startLoop(), serverAddr);
		client.connect();

		string line;
		while(getline(std::cin, line))
		{
			client.write(line);
		}
		client.disconnect();
	}
	else
	{
		printf("Usage: %s host_ip port\n", argv[0]);
	}
}

