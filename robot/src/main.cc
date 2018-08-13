/*************************************************************************
	> File Name: main.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年07月20日 星期五 23时20分57秒
 ************************************************************************/

#include <unistd.h>
#include "iomn.h"
#include "robot_define.h"
#include "logging.h"
#include <signal.h>
#include "robot_mgr.h"

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
uint32 ParseCommandLineFlags(int* argc, char*** argv, bool remove_flags);
}

int main(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc, &argv, true);

	ProcessSignal();

	LOG(INFO) << "robot server start";

	daemon(1, 1);

	IomnStart(ROBOT_SVR_NAME, TopIomnMenu);

	while(true)
	{
		RobotMgr::Instance().Update();
		usleep(10);
	}
	return 0;
}
