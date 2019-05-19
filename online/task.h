#ifndef TASK_H__
#define TASK_H__

#include "indexDict.h"
#include <string>

class Task
{
public:
	Task()
	: _dict(IndexDict::getInstance())
	{}

	string search(string str);
private:
	IndexDict* _dict;
	//vector<string> _searchResult;
private:
	int mininum_edist(const string& , const string& );
	int Min(int, int, int);
};


#endif
