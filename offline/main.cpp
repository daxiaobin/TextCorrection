#include "configuration.h"
#include "dictionary.h"
#include "log4.h"

int main()
{
//	Configuration conf("../conf");

/*	Dictionary dict_en( conf.getConMap()["corpus_english"], conf.getConMap()["dict_english"] );
	dict_en.showDictFile();
	dict_en.create_english_dict();
	dict_en.store_dict();
*/
/*	Dictionary dict_ch( conf.getConMap()["corpus_chinese"], conf.getConMap()["dict_chinese"] );
	dict_ch.showDictFile();
	dict_ch.create_chinese_dict();
	dict_ch.store_dict();
*/
	int a = 10;
	LogInfo("this is a info message, %d", a);
	return 0;
}
