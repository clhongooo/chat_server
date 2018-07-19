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
		LOG(ERROR) << "init robot failed!";
	}

	robot_id_ = tcsock_.get_sock_fd();
}

bool Robot::Connect()
{
	if(tcsock_.IsValid() && tcsock_.Connect(CHAT_SVR_IP, CHAT_SVR_PORT))
	{
		return true;
	}

	LOG(ERROR) << "robot connects to chat server failed!";
	return false;
}

bool Robot::Close()
{
	if(tcsock_.Close())
	{
		return true;
	}

	LOG(ERROR) << "robot[id:%d] close failed!" << robot_id_;
	return false;
}
