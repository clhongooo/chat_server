/*************************************************************************
	> File Name: main.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月23日 星期四 10时47分15秒
 ************************************************************************/

#include <iostream>
#include "chat_cli.h"
#include <unistd.h>
#include "socket_mgr.h"
#include "logging.h"
#include "iomn.h"
using namespace std;

extern void TopIomnMenu();

#define CHAT_CLI_NAME "@iomn_chatcli"

int main(int argc, char* argv[])
{
	if(SocketMgr::Instance().InitSocketMgr() == false)
	{
		LOG(ERROR) << "socket manager init error!";
		exit(EXIT_FAILURE);
	}

	if(ChatClient::Instance().InitChatClient(argc, argv) == false)
	{
		LOG(ERROR) << "chat client init error!";
		exit(EXIT_FAILURE);
	}

	

	daemon(1, 1);

	IomnStart(CHAT_CLI_NAME, TopIomnMenu);

	while(true)
	{
		ChatClient::Instance().Update();
	}
	return 0;
}
