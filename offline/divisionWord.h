#ifndef DIVISION_WORD_H
#define DIVISION_WORD_H

#include "../cppjieba/include/cppjieba/Jieba.hpp"
#include <vector>
#include <string>
using std::string;
using std::vector;

class Dictionary;
class DivisionWord{
	friend Dictionary;
private:
	void cut( const string& sentence );
private:
	vector<string> _result;
};





#endif
