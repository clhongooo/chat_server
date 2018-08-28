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
#include "base_type.h"
#include "head_define.h"

class ChatClient
{
public:
	ChatClient();
	~ChatClient();

	static ChatClient& Instance();

	ChatCliCfg& get_chat_cli_cfg() { return chat_cli_cfg_; }
	bool get_state() { return state_; }

	bool InitChatClient(int argc, char** arg);
	bool DisConnect();

	void SendPackage(uint32 msg_id, const PBMsg& msg, bool flag = false);
	void ReadPackage(char* data, int len);
	
	void Update();

	//send request protocol
	void OnReqAccountRegister(const char* acc, const char* pwd);
	void OnReqAccountLogin(const char* acc, const char* pwd);
	void OnReqAccountLogout();

	//deal with response protocol
	void OnResAccountRegister(char* data, int len);
	void OnResAccountLogin(char* data, int len);
	void OnResAccountLogout();

private:
	ChatCliCfg chat_cli_cfg_;
	shared_ptr<TcpSocket> sp_tcsock_;
	struct timeval cur_tv_;
	bool state_;
};

#endif//CHAT_CLI_H_
