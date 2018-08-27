/***************************************************************************
	> File Name: chat_svr_cfg.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月27日 星期一 09时58分02秒
 ************************************************************************/
#ifndef CHAT_SVR_CFG_H_
#define CHAT_SVR_CFG_H_

#include "config.h"

class ChatSvrCfg : public Config
{
public:
	ChatSvrCfg();
	~ChatSvrCfg();

	string& get_db_user() { return db_user_; }
	string& get_db_pwd() { return db_pwd_; }
	string& get_db_name() { return db_name_; }

	virtual int ParseFile(const char* file_name);

private:
	string db_user_;
	string db_pwd_;
	string db_name_;
};

#endif//CHAT_SVR_CFG_H_
