#include "LanguageManager.h"
#include "cocos2d.h"

using namespace cocos2d;

LanguageManager* LanguageManager::_instance = 0;

LanguageManager::LanguageManager()
{
	auto def = UserDefault::sharedUserDefault();
	auto languageCurrent = def->getStringForKey("LANGUAGE", "en");
	if (languageCurrent == "en")
		_fileName = "en.json"; // english language
	else
		if (languageCurrent == "vi")
			_fileName = "vi.json"; // vietnamese language
		else
			_fileName = "en.json"; // default languge
	ssize_t size;
	const char* buf = (const char*)FileUtils::getInstance()->getFileData(_fileName.c_str(), "r", &size);
	string content(buf);
	string clearContent = content.substr(0, content.rfind('}') + 1);
	_document.Parse<0>(clearContent.c_str());
}
LanguageManager::~LanguageManager()
{

}

LanguageManager* LanguageManager::getInstance()
{
	if (!_instance)
		_instance = new LanguageManager();
	return _instance;
}

string LanguageManager::getStringForKey(string key) const
{
	return _document[key.c_str()].GetString();
}
