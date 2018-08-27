/***************************************************************************
	> File Name: chat_svr.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月27日 星期一 10时15分39秒
 ************************************************************************/
#ifndef CHAT_SVR_H_
#define CHAT_SVR_H_

#include "acceptor.h"
#include "chat_svr_cfg.h"
#include <memory>

#include "database.hxx"
#include <odb/database.hxx>
#include <odb/transaction.hxx>

using namespace odb::core;

class ChatSvr
{
public:
	ChatSvr() {}
	~ChatSvr() {}

	odb::database* get_chat_db() { return chat_db_.get(); }

	static ChatSvr& Instance();

	bool InitChatSvr(const char* file_name);
	void InitDatabase();
	void Update();

private:
	Acceptor acceptor_;
	ChatSvrCfg chat_svr_cfg_;
	auto_ptr<odb::database> chat_db_;
};

#endif//CHAT_SVR_H_
