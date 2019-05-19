#include "cocos2d.h"
#include "wxsqlite/sqlite3.h"
class SQLiteManager {
private:
	SQLiteManager();
	static SQLiteManager* instance;
	sqlite3 *_db;
	bool open();
	void close();
public:
	virtual ~SQLiteManager();
	static SQLiteManager* getInstance();
	void insert(std::string key, std::string value);
	void update(std::string key, std::string value);
	std::string select(std::string key);
};