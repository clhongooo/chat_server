/*************************************************************************
	> File Name: chat_svr_cfg.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月27日 星期一 09时58分08秒
 ************************************************************************/

#include "chat_svr_cfg.h"
#include "logging.h"

ChatSvrCfg::ChatSvrCfg()
	: db_user_("")
	, db_pwd_("")
	, db_name_("")
{

}

ChatSvrCfg::~ChatSvrCfg()
{

}

int ChatSvrCfg::ParseFile(const char* file_name)
{
	if(Config::ParseFile(file_name) != -1)
	{	
		if(GetValueAsString("db_user", db_user_) == false)
		{
			LOG(ERROR) << "parse file error! db_user";
			return -1;
		}
		if(GetValueAsString("db_pwd", db_pwd_) == false)
		{
			LOG(ERROR) << "parse file error! db_pwd";
			return -1;
		}
		if(GetValueAsString("db_name", db_name_) == false)
		{
			LOG(ERROR) << "parse file error! db_name";
			return -1;
		}
		return 0;
	}

	return -1;
}
