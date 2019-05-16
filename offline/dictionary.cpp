#include "dictionary.h"
#include "divisionWord.h"
#include "log4.h"
#include <dirent.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

void Dictionary::getDictFile()
{
	struct dirent* pDirInfo;
	DIR* pDir;

	pDir = opendir( _dir.c_str() );
	if( NULL == pDir )
	{
		LogError( "open dir error" );
		return;
	}

	while( (pDirInfo = readdir(pDir)) != NULL )
	{
		string file_name( pDirInfo->d_name );
		if( file_name != static_cast<string>(".") && file_name != static_cast<string>("..") )
		{
			_dictFile.push_back( _dir + "/" + file_name);
		}
	}
	closedir(pDir);
}

void Dictionary::create_english_dict()
{
	for( auto it = _dictFile.begin(); it != _dictFile.end(); ++it )
	{
		string file = *it;
		ifstream ifs;
		ifs.open( file.c_str(), ios::in );
		if( !ifs.is_open() )
		{
			LogError("open file error");
			return;
		}

		string line, result, word;
		boost::regex reg("[^a-zA-Z ]");
		while( getline(ifs, line) )
		{
			result = boost::regex_replace( line, reg, "" );
			boost::algorithm::to_lower(result);		

			istringstream iss(result);
			while( iss >> word )
			{
				_result[word]++;
			}
		}
	}
}

void Dictionary::create_chinese_dict()
{
	for( auto it = _dictFile.begin(); it != _dictFile.end(); ++it )
	{
		ifstream ifs(*it);
		if( !ifs )
		{
			LogError( "open file error" );
			return;
		}

		string line, result, word, text;
		boost::regex reg("[^\u4E00-\u9FA5]");
		while( getline(ifs, line) )
		{
			result = boost::regex_replace( line, reg, "" );
			text += result;
		}

		DivisionWord dw;
		dw.cut( text );
		for( auto it = dw._result.begin(); it != dw._result.end(); ++it )
		{
			_result[*it]++;
		}

		ifs.close();
	}
}

void Dictionary::store_dict()
{
	ofstream ofs( _file.c_str() );
	if( !ofs )
	{
		LogError( "open file error" );
		return;
	}

	for( auto& elm : _result)
	{
		ofs << elm.first << " " << elm.second << endl;
	}

	ofs.close();
}
