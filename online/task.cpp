 ///
 /// @file    tash.cpp
 /// @author  daxiaobing(248918860@qq.com)
 /// @date    2019-05-17 20:39:21
 ///
 
#include "task.h"
#include <limits.h>
#include <algorithm>
#include <map>

using namespace std;

string Task::search(string s)
{
	//首先将str分解为一个一个的字母，然后对每个字母从_indexCharacter中取出对应的set<int>的下标合集，再对所有的set<int>取并集。
	//最后根据集合中的数字取出对应的_indexEnglish中的单词。
	//得到单词后将每个单词与str计算最小编辑距离
	string str = s;
	if(str.empty()) return string("");
	std::sort(str.begin(), str.end());
	auto last = std::unique(str.begin(), str.end());

	const map<char, set<int> >& indexCharacter = _dict->getIndexCharacter();
	auto search = indexCharacter.find(*(str.begin()));
	set<int> result_index = search->second;

	for(auto it = (str.begin() + 1); it != last; it++)
	{
		char ch = *it;
		auto search_next = indexCharacter.find(ch);
		const set<int>& tmp = search_next->second;
		result_index.insert(tmp.begin(), tmp.end());
	}
	const vector<pair<string,int>>& indexEnglish = _dict->getIndexEnglish();
	vector<pair<string, int>> result_word;
	for(const int& mem:result_index)
	{
		result_word.push_back(indexEnglish[mem]);
	}

	//计算最小编辑距离
	multimap<int, pair<string, int>> result_edist;
	for(auto& mem:result_word)
	{
		const string& str2 = mem.first;
		int min_edist = mininum_edist(s, str2);
		result_edist.insert(make_pair(min_edist, mem));
	}
	//取最终结果
	int k = result_edist.begin()->first;
	int m = result_edist.count(k);
	if(m > 1)
	{
		vector<pair<string, int>> result_final;
		multimap<int, pair<string, int>>::const_iterator it = result_edist.cbegin();
		for(int index = 0; index < m; index++, it++)	
		{
			result_final.push_back(it->second);
		}
		std::sort(result_final.begin(), result_final.end(), [](pair<string,int>& left, pair<string,int>& right){return left.second > right.second;});
		return result_final[0].first;
	}
	return (result_edist.begin()->second).first;
}

int Task::mininum_edist(const string& str1, const string& str2)
{
	vector<vector<int>> vvi;

	const unsigned int n = str1.size(); //n为行
	vvi.resize(n);
	const unsigned int m = str2.size(); //m为列
	for(unsigned int i = 0; i < n; i++)
	{
		vvi[i].resize(m, -1);
	}
	//初始化第0行
	for(unsigned int j = 0; j < m; j++)
	{
		if(str1[0] == str2[j]) vvi[0][j] = j;
		else if(j != 0) vvi[0][j] = vvi[0][j-1] + 1; 
		else vvi[0][j] = 1;
	}
	//初始化第0列
	for(unsigned int i = 0; i < n; i++)
	{
		if(str2[0] == str1[i]) vvi[i][0] = i;
		else if(i != 0) vvi[i][0] = vvi[i-1][0] + 1;
		else vvi[i][0] = 1;
	}
	//正式开始
	for(unsigned int i = 1; i < n; i++)
	{
		for(unsigned int j = 1; j < m; j++)
		{
			if(str1[i] == str2[j])
			{
				vvi[i][j] = Min(vvi[i-1][j]+1, vvi[i][j-1]+1, vvi[i-1][j-1]);
			}
			else vvi[i][j] = Min(vvi[i-1][j]+1, vvi[i][j-1]+1, vvi[i-1][j-1]+1);
		}
	}
	return vvi[n-1][m-1];
}

int Task::Min(int a, int b, int c)
{
	int min = INT_MAX;
	if(a < min) min = a;
	if(b < min) min = b;
	if(c < min) min = c;
	return min;
}
