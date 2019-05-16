#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class Configuration{
public:
	Configuration( const string& filePath )
	: _filePath(filePath)
	{
		makeMap();
	}
	~Configuration()
	{}

	void makeMap();

	map<string, string>& getConMap() 
	{	return _conMap;	}
private:
	const string _filePath;
	map<string,string> _conMap;
};


#endif
