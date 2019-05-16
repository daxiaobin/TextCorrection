#ifndef TASK_H__
#define TASK_H__

#include "indexDict.h"

class Task
{
public:
	Task()
	: _dict(IndexDict::getInstance())
	{}
private:
	IndexDict* _dict;
};




#endif
