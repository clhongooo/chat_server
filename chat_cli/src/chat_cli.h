/***************************************************************************
	> File Name: chat_cli.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月23日 星期四 17时35分01秒
 ************************************************************************/
#ifndef CHAT_CLI_H_
#define CHAT_CLI_H_

#include "chat_cli_cfg.h"

class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	ChatCliCfg& get_chat_cli_cfg() { return chat_cli_cfg_; }
	
	bool InitChatClient(int argc, char** arg);

private:
	ChatCliCfg chat_cli_cfg_;
};

#endif//CHAT_CLI_H_
