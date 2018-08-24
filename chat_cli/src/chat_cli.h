/***************************************************************************
	> File Name: chat_cli.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月23日 星期四 17时35分01秒
 ************************************************************************/
#ifndef CHAT_CLI_H_
#define CHAT_CLI_H_

#include "chat_cli_cfg.h"
#include "tcp_cli_socket.h"
#include <memory>
#include <sys/time.h>

class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	ChatCliCfg& get_chat_cli_cfg() { return chat_cli_cfg_; }
	
	bool InitChatClient(int argc, char** arg);
	bool DisConnect();

	void ReadPackage(char* data, int len);
	
	void Update();

private:
	ChatCliCfg chat_cli_cfg_;
	shared_ptr<TcpSocket> sp_tcsock_;
	struct timeval cur_tv_;
};

#endif//CHAT_CLI_H_
