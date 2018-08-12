/***************************************************************************
	> File Name: conn_mgr.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 07 Aug 2018 09:00:13 PM CST
 ************************************************************************/
#ifndef CONN_MGR_H_
#define CONN_MGR_H_

#include "chat_define.h"
#include <sys/time.h>

class ConnMgr
{
public:
	ConnMgr();
	~ConnMgr();
	
	static ConnMgr& Instance();
	
	bool InsertConnsMap(shared_ptr<ClientConn> sp_cli_conn);
	bool RemoveConnsMap(int client_id);

	void Update();

	template<typename Function>
	void for_each_client(Function func)
	{
		for(auto& item : client_conns_map_)
		{
			func(item.second);
		}
	}

private:
	ClientConnsMap client_conns_map_;	
	struct timeval cur_tv_;
};

#endif//CONN_MGR_H_
