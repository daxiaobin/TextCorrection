 ///
 /// @file    configuration.cpp
 /// @author  daxiaobing(248918860@qq.com)
 /// @date    2019-04-03 21:27:02
 ///
 
#include "configuration.h"
#include "log4.h"

void Configuration::makeMap()
{
	ifstream ifs( _filePath );
	if( !ifs )
	{
		LogError( "open file error" );
		return;
	}

	string line;
	string left, right;
	while( getline( ifs, line ) )
	{
		istringstream iss(line);
		iss >> left >> right;
		_conMap[left] = right;
	}
}
