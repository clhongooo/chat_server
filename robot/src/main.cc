/*************************************************************************
	> File Name: main.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年07月20日 星期五 23时20分57秒
 ************************************************************************/

#include<unistd.h>
#include<iomn.h>
#include<robot_define.h>
#include<logging.h>

extern void TopIomnMenu();

int main(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc, &argv, true);

	LOG(INFO) << "robot server start";

	daemon(1, 1);

	IomnStart(ROBOT_SVR_NAME, TopIomnMenu);
	
	while(true)
	{
		sleep(1);
	}
	return 0;
}