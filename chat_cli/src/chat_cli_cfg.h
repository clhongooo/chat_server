/***************************************************************************
	> File Name: chat_cli_cfg.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月23日 星期四 15时58分07秒
 ************************************************************************/
#ifndef CHAT_CLI_CFG_H_
#define CHAT_CLI_CFG_H_

#include "config.h"

class ChatCliCfg : public Config
{
public:
	ChatCliCfg();
	~ChatCliCfg();

	string get_svr_ip() { return svr_ip_; }
	int get_svr_port() { return svr_port_; }

	virtual int ParseFile(const char* file_name);

private:
	string svr_ip_;
	int svr_port_;
};

#endif//CHAT_CLI_CFG_H_
