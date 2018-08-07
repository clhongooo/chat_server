/*************************************************************************
	> File Name: chat_cli_mgr.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Tue 07 Aug 2018 10:17:55 AM CST
 ************************************************************************/

#include "conn_mgr.h"
#include "client_conn.h"

ConnMgr::ConnMgr()
{

}

ConnMgr::~ConnMgr()
{

}

ConnMgr& ConnMgr::Instance()
{
	static ConnMgr inst;
	return inst;
}

void ConnMgr::InsertConnsMap(shared_ptr<ClientConn> sp_client_conn)
{
	int client_id = sp_client_conn->get_client_id();
	if(client_conns_map_.find(client_id) != client_conns_map_.end())
	{
		return;
	}

	client_conns_map_[sp_client_conn->get_client_id()] = sp_client_conn;
}

void ConnMgr::RemoveConnsMap(int client_id)
{
	ClientConnsMap::iterator iter = client_conns_map_.find(client_id);
	if(iter != client_conns_map_.end())
	{
		client_conns_map_.erase(iter);
	}
}
