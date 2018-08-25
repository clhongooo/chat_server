/***************************************************************************
	> File Name: robot.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:42:58 PM CST
 ************************************************************************/
#ifndef ROBOT_H_
#define ROBOT_H_

#include "tcp_socket.h"
#include <memory>
#include "head_define.h"
#include "base_type.h"

class Robot
{
public:
	Robot() {}
	~Robot() {}

	int get_robot_id() { return robot_id_; }	
	shared_ptr<TcpSocket> get_tsock() { return spt_sock_; }

	bool InitRobot();
	bool Connect();
	bool Close();

	int DumpRobotInfo(char* buffer, int buff_len);
	void SendPackage(uint32 msg_id, const PBMsg& msg);
	void ReadPackage(char* data, int len);

private:
	shared_ptr<TcpSocket> spt_sock_;
	int robot_id_;
};

#endif//ROBOT_H_
