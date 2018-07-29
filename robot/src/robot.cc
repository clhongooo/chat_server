/*************************************************************************
	> File Name: robot.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:43:03 PM CST
 ************************************************************************/

#include<robot.h>
#include<logging.h>
#include<robot_define.h>
#include<sys/socket.h>

Robot::Robot()
{
	if(tcsock_.Create(SOCK_STREAM, 0) == false)
	{

	}

	robot_id_ = tcsock_.get_sock_fd();
}

bool Robot::Connect()
{
	if(!tcsock_.IsValid()) {
		fprintf(stderr, "tcsock is invalid\n");
		return false;
	}

	if(!tcsock_.Connect(CHAT_SVR_IP, CHAT_SVR_PORT))
	{
		fprintf(stderr, "robot connects to chat server failed!");
		return false;
	}

	return true;
}

bool Robot::Close()
{
	if(tcsock_.Close())
	{
		printf("robot close ok!\n");
		return true;
	}
	
	printf("robot close failed!\n");
	return false;
}

int Robot::DumpRobotInfo(char* buffer, int buff_len)
{
	int len = 0;
	len += snprintf(buffer+len, buff_len-len, "robot id:%d\n", robot_id_);
	return len;
}
