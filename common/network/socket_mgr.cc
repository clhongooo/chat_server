/*************************************************************************
	> File Name: socket_mgr.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Fri 06 Jul 2018 08:06:31 PM CST
 ************************************************************************/
#include<socket_mgr.h>
#include<tcp_socket.h>
#include<epoller.h>
#include<socket_define.h>
#include<tcp_svr_socket.h>
#include<logging.h>

SocketMgr::SocketMgr()
{

}

SocketMgr& SocketMgr::Instance()
{
	static SocketMgr socket_mgr;
	return socket_mgr;
}

void SocketMgr::RegisterSocketEvent(shared_ptr<TcpSocket> sptsock, int event_flags)
{
	epoller_.RegisterEvent(sptsock, event_flags);
}

void SocketMgr::UnRegisterSocketEvent(shared_ptr<TcpSocket> sptsock)
{
	epoller_.UnRegisterEvent(sptsock);
}

void SocketMgr::Update()
{
	CheckSocketEvent();
}

void SocketMgr::CheckSocketEvent()
{
	if(!epoller_.WaitForEvent(2000))
	{
		return;
	}

	int event_flags = 0;
	TcpSocket* tsock = NULL;
	while(epoller_.GetSocketEvent(tsock, event_flags))
	{
		if(tsock == NULL)
		{
			continue;
		}
		
		if(!tsock->IsValid() || tsock->get_sock_state() == SS_INVALID)
		{
			continue;
		}

		if(event_flags & SOCKET_EVENT_ON_EXCEPT)
		{
			ProcessClose(*tsock);
			continue;
		}

		if(tsock->get_sock_state() == SS_LISTENING && (event_flags & SOCKET_EVENT_ON_READ))
		{
			TcpSvrSocket* tssock = dynamic_cast<TcpSvrSocket*>(tsock);
			if(tssock)
			{
				ProcessAccept(*tssock);
			}
			continue;
		}

		if(tsock->get_sock_state() == SS_CONNECTED && (event_flags & SOCKET_EVENT_ON_READ))
		{
			ProcessRead(*tsock);
		}

		if(tsock->get_sock_state() == SS_CONNECTED && (event_flags & SOCKET_EVENT_ON_WRITE))
		{
			ProcessWrite(*tsock);
		}
	}
}

void SocketMgr::ProcessClose(TcpSocket& ts)
{
	CloseCallBack close_cb = ts.get_close_call_back();
	close_cb();
}

void SocketMgr::ProcessAccept(TcpSvrSocket& ts)
{
	AcceptCallBack accept_cb = ts.get_accept_call_back();
	accept_cb();
}

void SocketMgr::ProcessRead(TcpSocket& ts)
{
	ts.Read();
}

void SocketMgr::ProcessWrite(TcpSocket& ts)
{
	ts.Write();
}
