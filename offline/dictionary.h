#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
using std::cout;
using std::endl;

using namespace std;

class Dictionary{
public:
	Dictionary(const string& dir, const string& file)
	: _dir(dir)
	, _file(file)
	{	getDictFile();	}

	void create_chinese_dict();
	void create_english_dict();
	void store_dict();
	void showDictFile() const;
private:
	void getDictFile();
private:
	string _dir; //语料库的目录
	string _file; //存放词典的文件
	vector<string> _dictFile; //语料库目录里的文件
	map<string, int> _result; //词典文件的内容
};

inline
void Dictionary::showDictFile() const
{
	for( auto it = _dictFile.cbegin(); it != _dictFile.cend(); ++it )
	{
		cout << *it << endl;
	}
}



#endif 
