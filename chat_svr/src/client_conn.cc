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
#include "account.pb.h"
#include "error.pb.h"
#include "msg_wrapper.h"

#include "chat_svr.h"
#include "account_info.hxx"
#include "account_info-odb.hxx"
using namespace odb::core;

ClientConn::ClientConn()
	: state_(false)
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
				HandleAccountRegister(data+head_len, len-head_len);
			break;
		case Pb::CS_CMD_REQ_ACCOUNT_LOGIN:
				HandleAccountLogin(data+head_len, len-head_len);
			break;
		case Pb::CS_CMD_REQ_ACCOUNT_LOGOUT:
				HandleAccountLogout(data+head_len, len-head_len);
			break;
		default:
			break;
	}
	
	spt_sock_->RemoveRecvPkg(len);
}

void ClientConn::SendPackage(uint32 msg_id, const PBMsg& msg, bool flag)
{
	if(spt_sock_->IsValid() == false)
	{
		return;
	}

	char* buffer = new char[10*1024];
	int msg_len = MsgWrapper::EncodeComMsg(buffer, 10*1024, msg_id, msg);
	spt_sock_->SendPackage(buffer, msg_len, flag);
	delete[] buffer;
}

int ClientConn::DumpClientConnInfo(char* buffer, int buff_len)
{
	int len = 0;
	len += snprintf(buffer+len, buff_len-len, "client id:%d,\t sock_fd:%d\n", client_id_, spt_sock_->get_sock_fd());
	
	return len;
}

/*********************** handle request *******************************/

void ClientConn::HandleAccountRegister(char* data, int len)
{
	Pb::CSReqAccountRegister pkg;
	pkg.ParseFromArray(data, len);

	odb::database* chat_db = ChatSvr::Instance().get_chat_db();
	if(chat_db == NULL)
	{
		return;
	}

	typedef odb::query<AccountInfo> query;
	typedef odb::result<AccountInfo> result;

	Pb::CSResAccountRegister msg;
	msg.set_user_name(pkg.user_name());
	msg.set_result(true);

	//check account
	{
		transaction t(chat_db->begin());
		result r (chat_db->query<AccountInfo> (query::user_name == pkg.user_name()));
		if(r.empty() == false)
		{
			msg.set_result(false);
		}
		t.commit();
	}

	//insert account
	{
		if(msg.result())
		{
			AccountInfo account(pkg.user_name(), pkg.user_pwd());
			transaction t(chat_db->begin());
			chat_db->persist(account);
			t.commit();
		}
	}

	SendPackage(Pb::CS_CMD_RES_ACCOUNT_REGISTER, msg);
}

void ClientConn::HandleAccountLogin(char* data, int len)
{
	Pb::CSReqAccountLogin pkg;
	pkg.ParseFromArray(data, len);

	odb::database* chat_db = ChatSvr::Instance().get_chat_db();
	if(chat_db == NULL)
	{
		return;
	}

	typedef odb::query<AccountInfo> query;
	typedef odb::result<AccountInfo> result;

	Pb::CSResAccountLogin msg;
	msg.set_user_name(pkg.user_name());
	msg.set_result(Pb::ERROR_CODE_COMMON_SUCCESS);
	if(state_)
	{
		msg.set_result(Pb::ERROR_CODE_ACCOUNT_ALREADY_LOGIN);
	}
	else
	{
		//check account
		{
			transaction t(chat_db->begin());
			result r (chat_db->query<AccountInfo> (query::user_name == pkg.user_name()));
			int account_count = r.size();
			if(account_count == 0)
			{
				msg.set_result(Pb::ERROR_CODE_ACCOUNT_NOT_EXIST);
			}
			else if(r.size() > 1)
			{
				msg.set_result(Pb::ERROR_CODE_ACCOUNT_EXCEPTION);
			}
			else
			{
				result::iterator iter = r.begin();
				if(iter->user_pwd() != pkg.user_pwd())
				{
					msg.set_result(Pb::ERROR_CODE_ACCOUNT_PASSWORD_FAIL);
				}
				else
				{
					state_ = true;
				}
			}
			t.commit();
		}
	}

	SendPackage(Pb::CS_CMD_RES_ACCOUNT_LOGIN, msg);
}

void ClientConn::HandleAccountLogout(char* data, int len)
{
	Pb::CSResAccountLogout msg;
	SendPackage(Pb::CS_CMD_RES_ACCOUNT_LOGOUT, msg);
}
