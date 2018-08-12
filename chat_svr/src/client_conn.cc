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
		ConnMgr::Instance().RemoveConnsMap(client_id_);
	}
	else
	{
		LOG(ERROR) << "connect closes failly!client id:" << client_id_;
	}
}

void ClientConn::ReadPackage(char* data, int len)
{
	printf("\nread data:%s,len:%d\n", data, len);
	spt_sock_->RemoveRecvPkg(len);
}

int ClientConn::DumpClientConnInfo(char* buffer, int buff_len)
{
	int len = 0;
	len += snprintf(buffer+len, buff_len-len, "client id:%d,\t sock_fd:%d\n", client_id_, spt_sock_->get_sock_fd());
	
	return len;
}
