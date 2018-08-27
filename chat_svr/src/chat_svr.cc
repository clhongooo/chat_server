/*************************************************************************
	> File Name: chat_svr.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月27日 星期一 10时15分44秒
 ************************************************************************/

#include "chat_svr.h"
#include "logging.h"
#include "socket_mgr.h"

ChatSvr& ChatSvr::Instance()
{
	static ChatSvr inst;
	return inst;
}

bool ChatSvr::InitChatSvr(const char* file_name)
{
	cout << "file name:" << file_name << endl;
	if(chat_svr_cfg_.ParseFile(file_name) == -1)
	{
		LOG(ERROR) << "chat svr config parse error!" << file_name;
		return false;
	}

	if(SocketMgr::Instance().InitSocketMgr() == false)
	{
		LOG(ERROR) << "init socket manager error";
		return false;
	}

	if(acceptor_.InitAcceptor() == false)
	{
		LOG(ERROR) << "init acceptor error!";
		return false;
	}

	InitDatabase();

	return true;
}

void ChatSvr::InitDatabase()
{
	int paramc = 6;
	char* params[] = {
		"--user",
		&(chat_svr_cfg_.get_db_user())[0],
		"--password",
		&(chat_svr_cfg_.get_db_pwd())[0],
		"--database",
		&(chat_svr_cfg_.get_db_name())[0]
	};

	chat_db_ = create_database(paramc, (char**)(void*)params);
}
