/***************************************************************************
	> File Name: db_mysql.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月16日 星期四 16时26分27秒
 ************************************************************************/
#ifndef DB_MYSQL_H_
#define DB_MYSQL_H_

#include <iostream>
#include <mysql/mysql.h>
#include <string>
using namespace std;

class DBMysql
{
public:
	DBMysql();
	~DBMysql() {}

	MYSQL* get_mysql() { return &mysql_; }
	
	bool InitDBMysql();
	bool Connect();
	bool DisConnect();

private:
	bool connected_;
	string str_user_;
	string str_pwd_;
	string str_ip_;
	int port_;
	MYSQL mysql_;
};

#endif//DB_MYSQL_H_
