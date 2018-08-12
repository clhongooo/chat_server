/*************************************************************************
	> File Name: chat_cli_mgr.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Tue 07 Aug 2018 10:17:55 AM CST
 ************************************************************************/

#include "conn_mgr.h"
#include "client_conn.h"
#include "logging.h"

ConnMgr::ConnMgr()
{
	gettimeofday(&cur_tv_, NULL);
}

ConnMgr::~ConnMgr()
{

}

ConnMgr& ConnMgr::Instance()
{
	static ConnMgr inst;
	return inst;
}

bool ConnMgr::InsertConnsMap(shared_ptr<ClientConn> sp_client_conn)
{
	int client_id = sp_client_conn->get_client_id();
	if(client_conns_map_.find(client_id) != client_conns_map_.end())
	{
		return false;
	}
	
	client_conns_map_[sp_client_conn->get_client_id()] = sp_client_conn;
	return true;
}

bool ConnMgr::RemoveConnsMap(int client_id)
{
	ClientConnsMap::iterator iter = client_conns_map_.find(client_id);
	if(iter != client_conns_map_.end())
	{
		client_conns_map_.erase(iter);
		return true;
	}
	return false;
}

struct tagUpdateSendCache
{
	int operator()(shared_ptr<ClientConn> sp_client_conn)
	{
		sp_client_conn->get_spsock()->SendCache();
		return 0;
	}
};

void ConnMgr::Update()
{
	struct timeval now_tv;
	gettimeofday(&now_tv, NULL);
	int now_tv_msec = now_tv.tv_sec*1000 + now_tv.tv_usec/1000;
	int last_tv_msec = cur_tv_.tv_sec*1000 + cur_tv_.tv_usec/1000;
	
	if(now_tv_msec - last_tv_msec >= 20)
	{
		tagUpdateSendCache tag_send_cache;
		for_each_client(tag_send_cache);
	}
}
