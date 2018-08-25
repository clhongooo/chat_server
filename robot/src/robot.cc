/*************************************************************************
	> File Name: robot.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:43:03 PM CST
 ************************************************************************/

#include "robot.h"
#include "logging.h"
#include "robot_define.h"
#include "sys/socket.h"
#include <memory>
#include "socket_define.h"
#include "socket_mgr.h"
#include "tcp_cli_socket.h"
#include "head_define.h"
#include "msg_wrapper.h"
#include "msg_test.pb.h"
#include "msg_head.h"

bool Robot::InitRobot()
{
	spt_sock_ = shared_ptr<TcpSocket>(new TcpCliSocket);
	if(spt_sock_->Create(SOCK_STREAM, 0) == false)
	{
		return false;		
	}

	robot_id_ = spt_sock_->get_sock_fd();
	return true;
}

bool Robot::Connect()
{
	if(spt_sock_->IsValid() == false) 
	{
		return false;
	}

	TcpCliSocket* tc_sock = static_cast<TcpCliSocket*>(spt_sock_.get());
	if(tc_sock == NULL)
	{
		return false;
	}

	if(tc_sock->Connect(CHAT_SVR_IP, CHAT_SVR_PORT) == false)
	{
		return false;
	}

	CloseCallBack close_cb = std::bind(&Robot::Close, this);
	spt_sock_->set_close_call_back(close_cb);
	using std::placeholders::_1;
	using std::placeholders::_2;
	ReadCallBack read_cb = std::bind(&Robot::ReadPackage, this, _1, _2);
	spt_sock_->set_read_call_back(read_cb);
	SocketMgr::Instance().RegisterSocketEvent(spt_sock_, SOCKET_EVENT_ON_READ | SOCKET_EVENT_ON_WRITE);
	
	return true;
}

bool Robot::Close()
{
	if(spt_sock_->Close())
	{
		SocketMgr::Instance().UnRegisterSocketEvent(spt_sock_);
		return true;
	}
	
	return false;
}

int Robot::DumpRobotInfo(char* buffer, int buff_len)
{
	int len = 0;
	len += snprintf(buffer+len, buff_len-len, "robot id:%d, robot socket fd:%d\n", robot_id_, spt_sock_->get_sock_fd());
	return len;
}

void Robot::SendPackage(uint32 msg_id, const PBMsg& msg)
{
	if(!spt_sock_->IsValid())
	{
		return;
	}

	char* buffer = new char[10*1024];
	int msg_len = MsgWrapper::EncodeComMsg(buffer, 10*1024, msg_id, msg);
	spt_sock_->SendPackage(buffer, msg_len);
	delete[] buffer;
}

void Robot::ReadPackage(char* data, int len)
{
	uint32 msg_id = 0;
	//int head_len = MsgWrapper::DecodeMsgHead(data, len, msg_id);
	
	switch(msg_id)
	{
		default:
			break;
	}
	
	spt_sock_->RemoveRecvPkg(len);
}
