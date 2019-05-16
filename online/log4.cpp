 ///
 /// @file    log4.cpp
 /// @author  daxiaobing(248918860@qq.com)
 /// @date    2019-04-01 10:40:28
 ///

#include "log4.h"
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <iostream>

MyLogger* MyLogger::_pInstance = NULL;

MyLogger* MyLogger::getInstance()
{
	if( _pInstance == NULL )
	{
		_pInstance = new MyLogger();
	}
	return _pInstance;
}

void MyLogger::destroy()
{
	if( _pInstance )
		delete _pInstance;
}

MyLogger::MyLogger()
: _category( log4cpp::Category::getRoot() )
{
	using namespace log4cpp;
	PatternLayout * ptnLayout1 = new PatternLayout();
	ptnLayout1->setConversionPattern("%d [%p] %m%n");

	PatternLayout * ptnLayout2 = new PatternLayout();
	ptnLayout2->setConversionPattern("%d [%p] %m%n");

	OstreamAppender * pOstreamAppender = new OstreamAppender("pOstreamAppender", &std::cout);
	pOstreamAppender->setLayout(ptnLayout1);

	FileAppender * pFileAppender = new FileAppender("pFileAppender", "project1.log");
	pFileAppender->setLayout(ptnLayout2);

	_category.addAppender(pOstreamAppender);
	_category.addAppender(pFileAppender);
	_category.setPriority(Priority::DEBUG);
}

MyLogger::~MyLogger()
{
	log4cpp::Category::shutdown();
}

void MyLogger::warn(const char * msg) 
{
	_category.warn(msg);
}

void MyLogger::error(const char * msg) 
{
	_category.error(msg);
}

void MyLogger::info(const char * msg) 
{
	_category.info(msg);
}

void MyLogger::debug(const char * msg) 
{
	_category.debug(msg);
}
