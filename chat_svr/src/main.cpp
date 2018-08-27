/*************************************************************************
	> File Name: main.cpp
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 03 Jul 2018 04:12:51 PM CST
 ************************************************************************/
#include<logging.h>
#include<memory>
#include<unistd.h>
#include<signal.h>
#include "chat_define.h"
#include "iomn.h"
#include "chat_svr.h"

extern void TopIomnMenu();

void ProcessSignal()
{
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

namespace google {
extern uint32 ParseCommandLineFlags(int* argc, char*** argv, bool remove_flags);
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		LOG(ERROR) << "parameter error!" << argc;
		return -1;
	}
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc, &argv, true);

	ProcessSignal();

	if(ChatSvr::Instance().InitChatSvr(argv[1]) == false)
	{
		LOG(ERROR) << "init chat server error";
		return -1;
	}

	daemon(1, 1);

	IomnStart(CHAT_SVR_NAME, TopIomnMenu);

	while(true)
	{
		ChatSvr::Instance().Update();
	}

	return 0;
}

