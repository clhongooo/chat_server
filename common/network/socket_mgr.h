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
class TcpSvrSocket;

class SocketMgr
{
public:
	SocketMgr();
	~SocketMgr() {}

	static SocketMgr& Instance();

	void RegisterSocketEvent(shared_ptr<TcpSocket>& sptsock, int event_flags);
	void UnRegisterSocketEvent(shared_ptr<TcpSocket>& sptsock);

	void Update();
	void CheckSocketEvent();

private:
	void ProcessClose(TcpSocket& ts);
	void ProcessAccept(TcpSvrSocket& ts);
	void ProcessRead(TcpSocket& ts);
	void ProcessWrite(TcpSocket& ts);

private:
	Epoller epoller_;
};

#endif//SOCKET_MGR_H_
