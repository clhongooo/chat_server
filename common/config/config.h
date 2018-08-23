/***************************************************************************
	> File Name: config.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月23日 星期四 11时01分46秒
 ************************************************************************/
#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <iostream>
using namespace std;

class Config
{
public:
	Config();
	virtual ~Config();

	virtual int ParseFile(const char* file_name);
	
	bool GetValueAsInt(const char* feild, int& v);
	bool GetValueAsString(const char* feild, string& v);

private:
	void GetStrByFeild(const char* feild, string& rv);
	
private:
	FILE* conf_file_;	
};

#endif//CONFIG_H_
