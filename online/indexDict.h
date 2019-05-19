#ifndef INDEXDICT_H
#define INDEXDICT_H

#include <vector>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

class IndexDict
{
public:
	class AutoRelease
	{
	public:
		~AutoRelease()
		{
			delete _instance;
		}
	};
public:
	static IndexDict* getInstance() 
	{
		if( _instance == nullptr)
		{
			_instance = new IndexDict();
		}
		return _instance;
	}

	vector<pair<string, int> >& getIndexEnglish() 
	{	return _indexEnglish;	}

	map<char, set<int> >& getIndexCharacter()
	{	return _indexCharacter;	}

	void display() 
	{
		for(auto it = _indexCharacter.begin(); it != _indexCharacter.end(); ++it)
		{
			cout << it->first << endl;
		}
	}
private:
	IndexDict()
	{
		_indexEnglish.reserve( 10000 );
		getPath();
		createIndexEnglish();
		createIndexCharacter();
	}

	void getPath();
	void createIndexEnglish();
	void createIndexCharacter();
private:
	string _english_path;
	string _chinese_path;
	vector<pair<string, int> > _indexEnglish;
	map<char, set<int> > _indexCharacter;
	static IndexDict* _instance;
	static AutoRelease _ar; //该对象位于全局静态区，在main函数执行完之后会销毁该对象，从而调用AutoRelease的析构函数。该对象的构造也是在main函数执行前进行的。
};


#endif
