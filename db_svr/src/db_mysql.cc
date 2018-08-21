/*************************************************************************
	> File Name: db_mysql.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月16日 星期四 16时26分36秒
 ************************************************************************/

#include "db_mysql.h"

DBMysql::DBMysql()
	: connected_(false)
	, str_user_("root")
	, str_pwd_("clhongooo")
	, str_ip_("127.0.0.1")
	, port_(3306)
{
	
}

bool DBMysql::InitDBMysql()
{
	if(mysql_library_init(0, NULL, NULL))
	{
		fprintf(stderr, "mysql_library_init failed!error:%s", mysql_error(&mysql_));
		return false;
	}

	if(mysql_init(&mysql_) == NULL)
	{
		fprintf(stderr, "mysql_init failed!error:%s", mysql_error(&mysql_));
		cout << "mysql_init fails!" << endl;
		return false;
	}

	return true;
}

bool DBMysql::Connect()
{
	if(mysql_real_connect(&mysql_, str_ip_.c_str(), str_user_.c_str(),
				str_pwd_.c_str(), NULL, port_, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
	{
		fprintf(stderr, "mysql_real_connect failed!error:%s,%d", mysql_error(&mysql_), errno);
		return false;
	}
	connected_ = true;
	return true;
}

bool DBMysql::DisConnect()
{
	if(connected_)
	{
		mysql_close(&mysql_);
		connected_ = false;
	}
	return true;
}
