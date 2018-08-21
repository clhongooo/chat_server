/*************************************************************************
	> File Name: main.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月16日 星期四 16时24分02秒
 ************************************************************************/

#include <iostream>
#include "db_mysql.h"
using namespace std;

int main()
{
	DBMysql db_mysql;
	db_mysql.InitDBMysql();
	if(db_mysql.Connect())
	{
		LOG(ERROR) << "db connect failed!";
	}
	db_mysql.DisConnect();
	return 0;
}
