/*************************************************************************
	> File Name: client.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Tue 07 Aug 2018 10:17:41 AM CST
 ************************************************************************/

#include "client_conn.h"
//#include "conn_mgr.h"

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
		//ConnMgr::Instance().RemoveConnsMap(client_id_);
	}
}

void ClientConn::ReadPackage(char* data, int len)
{
	printf("\nread data:%s\n", data);
}
