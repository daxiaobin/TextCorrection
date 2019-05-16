#include "divisionWord.h"
#include "log4.h"

void DivisionWord::cut( const string& sentence )
{
	const char * const DICT_PATH = "/home/lucky/c++/new_project1/cppjieba/dict/jieba.dict.utf8";//最大概率法(MPSegment: Max Probabili
	const char * const HMM_PATH = "/home/lucky/c++/new_project1/cppjieba/dict/hmm_model.utf8";//隐式马尔科夫模型(HMMSegment: Hidden M
	const char * const USER_DICT_PATH = "/home/lucky/c++/new_project1/cppjieba/dict/user.dict.utf8";//用户自定义词典路径
	const char* const IDF_PATH = "/home/lucky/c++/new_project1/cppjieba/dict/idf.utf8";//IDF路径
	const char* const STOP_WORD_PATH = "/home/lucky/c++/new_project1/cppjieba/dict/stop_words.utf8";//停用词路径))onst char* const STOP_WORD_PATH = "../dict/stop_words.utf8";
	cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);
	jieba.Cut( sentence, _result, true );
	LogInfo( "Continue" );
}
