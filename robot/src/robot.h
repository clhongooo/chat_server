/***************************************************************************
	> File Name: robot.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:42:58 PM CST
 ************************************************************************/
#ifndef ROBOT_H_
#define ROBOT_H_

#include<tcp_cli_socket.h>

class Robot
{
public:
	Robot();
	~Robot() {}

	int get_robot_id() { return robot_id_; }	
	
	bool Connect();
	bool Close();

	int DumpRobotInfo(char* buffer, int buff_len);

private:
	TcpCliSocket tcsock_;
	int robot_id_;
};

#endif//ROBOT_H_
