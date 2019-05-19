#ifndef __LANGUAGEMANAGER_SCENE_H__
#define __LANGUAGEMANAGER_SCENE_H__
#include <string>
#include "json/rapidjson.h"
#include "json/document.h"

using namespace rapidjson;
using std::string;

class LanguageManager
{
public:
	static LanguageManager* getInstance(); 
	string getStringForKey(string key) const;
private:
	static LanguageManager* _instance;

	LanguageManager();
	virtual ~LanguageManager();

	Document _document;
	string _fileName;
};

#endif // __LANGUAGEMANAGER_SCENE_H__
