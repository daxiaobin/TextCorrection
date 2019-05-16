#ifndef _MYLOGGER_H__
#define _MYLOGGER_H__


#include <log4cpp/Category.hh>
#include <string>

using std::string;

class MyLogger
{
public:
	static MyLogger* getInstance();
	static void destroy();

	void warn(const char* msg);
	template <typename... Args>
	void warn(const char* msg, Args... args)
	{
		_category.warn( msg, args... );
	}

	void error(const char * msg);
	template <typename... Args>
	void error(const char * msg, Args... args)
	{
		_category.error(msg, args...);
	}

	void info(const char * msg);
	template <typename... Args>
	void info(const char * msg, Args... args)
	{
		_category.info(msg, args...);
	}

	void debug(const char * msg);
	template <typename... Args>
	void debug(const char * msg, Args... args)
	{
		_category.debug(msg, args...);
	}
private:
	MyLogger();
	~MyLogger();
private:
	static MyLogger* _pInstance;
	log4cpp::Category& _category;
};

//#define LogInfo(msg, ...) MyLogger::getInstance()->info(string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(std::to_string(__LINE__)).append("] ").append(msg).c_str(),##__VA_ARGS__)
#define LogWarn(msg, ...) MyLogger::getInstance()->warn(string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(std::to_string(__LINE__)).append("] ").append(msg).c_str(),##__VA_ARGS__)
#define LogError(msg, ...) MyLogger::getInstance()->error(string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(std::to_string(__LINE__)).append("] ").append(msg).c_str(),##__VA_ARGS__)
#define LogDebug(msg, ...) MyLogger::getInstance()->debug(string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(std::to_string(__LINE__)).append("] ").append(msg).c_str(),##__VA_ARGS__)

#define LogInfo(msg, ...) MyLogger::getInstance()->info(string("[").append(__FILE__).append(":").append(":").append(std::to_string(__LINE__)).append("] ").append(msg).c_str(),##__VA_ARGS__)
#endif
