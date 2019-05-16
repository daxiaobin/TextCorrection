#include "indexDict.h"
#include "log4.h"
#include <fstream>

IndexDict* IndexDict::_instance = nullptr;
IndexDict::AutoRelease IndexDict::_ar; //初始实例化一个静态对象。

void IndexDict::getPath()
{
	ifstream ifs("../conf");
	if(!ifs)
	{
		LogError("open file error");
		exit(1);
	}
	string line, word;
	while(getline(ifs, line))
	{
		istringstream iss(line);
		iss >> word;
		if(word == string("dict_english"))
		{
			iss >> _english_path;
		}
		if(word == string("dict_chinese"))
		{
			iss >> _chinese_path;
		}
	}
}

void IndexDict::createIndexEnglish()
{
	ifstream ifs(_english_path);
	if( !ifs )
	{
		LogError( "open file error" );
		return;
	}

	pair<string, int> temp;
	while( ifs )
	{
		ifs >> temp.first >> temp.second;
		_indexEnglish.push_back(temp);
	}
	//写这两句是因为不知道为什么ifs直接输出到temp中最后一行会多输出一次。
	auto it = --_indexEnglish.end();
	_indexEnglish.erase( it );
}

void IndexDict::createIndexCharacter()
{
	unsigned int number = 0;
	string temp;
	for( auto it = _indexEnglish.begin(); it != _indexEnglish.end(); ++it )
	{
		temp = it->first;
		for( auto ch = temp.begin(); ch != temp.end(); ++ch )
		{
			_indexCharacter[*ch].insert(number);
		}
		++number;
	}
}
