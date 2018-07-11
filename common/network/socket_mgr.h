/***************************************************************************
	> File Name: socket_mgr.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Fri 06 Jul 2018 08:06:24 PM CST
 ************************************************************************/
#ifndef SOCKET_MGR_H_
#define SOCKET_MGR_H_

#include<socket_define.h>
#include<epoller.h>
#include<memory>

class TcpSocket;

class SocketMgr
{
public:
	SocketMgr();
	~SocketMgr() {}

	static SocketMgr& Instance();

	void InsertTcpSocket(shared_ptr<TcpSocket>& tsock);
	void RemoveTcpSocket(int sock_fd);

	void Update();
	void CheckSocketEvent();

private:
	SocksMap socks_map_;
	Epoller epoller_;
};

#endif//SOCKET_MGR_H_
