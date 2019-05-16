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

/*#ifdef __cplusplus
extern "C"{
#endif

#define prefix(msg) string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(std::to_string(__LINE__)).append("] ").append(msg).c_str()

#ifdef __cplusplus
}
#endif*/
inline 
string prefix( const char* msg )
{
	return string("[").append(__FILE__).append(":").append(__FUNCTION__).append(":").append(std::to_string(__LINE__)).append("] ").append(msg);
}

/*#define LogWarn(msg) MyLogger::getInstance()->warn(prefix(msg))
#define LogError(msg) MyLogger::getInstance()->error(prefix(msg))
#define LogInfo(msg) MyLogger::getInstance()->info(prefix(msg))
#define LogDebug(msg) MyLogger::getInstance()->debug(prefix(msg))
*/
inline
void LogError( const char* msg )
{
	MyLogger::getInstance()->error( prefix(msg).c_str() );
}

/*
inline
void LogInfo( const char* msg )
{
	MyLogger::getInstance()->info( prefix(msg).c_str() );
}*/
#define LogInfo(msg, ...) MyLogger::getInstance()->info(prefix(msg).c_str(), ##__VA_ARGS__)

inline
void LogWarn( const char* msg )
{
	MyLogger::getInstance()->warn( prefix(msg).c_str() );
}

inline
void LogDebug( const char* msg )
{
	MyLogger::getInstance()->debug( prefix(msg).c_str() );
}
#endif
