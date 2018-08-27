/*************************************************************************
	> File Name: client.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Tue 07 Aug 2018 10:17:41 AM CST
 ************************************************************************/

#include "client_conn.h"
#include "conn_mgr.h"
#include <stdio.h>
#include "logging.h"
#include "socket_mgr.h"
#include "msg_test.pb.h"
#include "msg_wrapper.h"

#include "chat_svr.h"
#include "account_info.hxx"
#include "account_info-odb.hxx"
using namespace odb::core;

ClientConn::ClientConn()
{

}

ClientConn::~ClientConn()
{

}

void ClientConn::CloseClientConn()
{
	if(spt_sock_->Close())
	{
		SocketMgr::Instance().UnRegisterSocketEvent(spt_sock_);
		ConnMgr::Instance().RemoveConnsMap(client_id_);
	}
	else
	{
		LOG(ERROR) << "connect closes failly!client id:" << client_id_;
	}
}

void ClientConn::ReadPackage(char* data, int len)
{
	uint32 msg_id = 0;
	int head_len = MsgWrapper::DecodeMsgHead(data, len, msg_id);
	
	switch(msg_id)
	{
		case Pb::CS_CMD_REQ_ACCOUNT_REGISTER:
			{
				HandleAccountRegister(data+head_len, len-head_len);
			}
			break;
		default:
			break;
	}
	
	spt_sock_->RemoveRecvPkg(len);
}

void ClientConn::SendPackage(uint32 msg_id, const PBMsg& msg)
{
	if(spt_sock_->IsValid() == false)
	{
		return;
	}

	char* buffer = new char[10*1024];
	int msg_len = MsgWrapper::EncodeComMsg(buffer, 10*1024, msg_id, msg);
	spt_sock_->SendPackage(buffer, msg_len);
	delete[] buffer;
}

int ClientConn::DumpClientConnInfo(char* buffer, int buff_len)
{
	int len = 0;
	len += snprintf(buffer+len, buff_len-len, "client id:%d,\t sock_fd:%d\n", client_id_, spt_sock_->get_sock_fd());
	
	return len;
}

void ClientConn::HandleAccountRegister(char* data, int len)
{
	Pb::CSReqAccountRegister pkg;
	pkg.ParseFromArray(data, len);

	odb::database* chat_db = ChatSvr::Instance().get_chat_db();
	if(chat_db == NULL)
	{
		return;
	}

	AccountInfo account(pkg.user_name(), pkg.user_pwd());
	transaction t(chat_db->begin());
	chat_db->persist(account);
	t.commit();
}
