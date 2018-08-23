/*************************************************************************
	> File Name: config.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月23日 星期四 11时01分52秒
 ************************************************************************/

#include "config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Config::Config()
	: conf_file_(NULL)
{

}

Config::~Config()
{
	fclose(conf_file_);
}

int Config::ParseFile(const char* file_name)
{
	conf_file_ = fopen(file_name, "r");
	if(conf_file_ == NULL)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	return 0;
}

bool Config::GetValueAsInt(const char* feild, int& v)
{
	string str_res;
	GetStrByFeild(feild, str_res);
	v = atoi(str_res.c_str());
	return true;
}

bool Config::GetValueAsString(const char* feild, string& v)
{
	GetStrByFeild(feild, v);
	return true;
}

void Config::GetStrByFeild(const char* feild, string& rv)
{
	if(feild == NULL || strlen(feild) == 0)
	{
		return;
	}
	
	size_t len = 0;
	ssize_t nread = 0;
	char* line = NULL, *equal = NULL;
	while((nread = getline(&line, &len, conf_file_)) != -1)
	{
		if(len && strstr(line, feild) == line)
		{
			equal = strstr(line, "=");
			break;
		}
	}
	equal++;
	while(*equal != '\n')
	{		
		if(*equal != ' ' && *equal != '\t')
		{
			break;
		}
		equal++;
	}

	rv = string(equal);
	rv = rv.substr(0, rv.size() - 1);
	fseek(conf_file_, 0, SEEK_SET);
}
