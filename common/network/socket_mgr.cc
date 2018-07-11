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

SocketMgr::SocketMgr()
{
	socks_map_.clear();
}

SocketMgr& SocketMgr::Instance()
{
	static SocketMgr socket_mgr;
	return socket_mgr;
}

void SocketMgr::InsertTcpSocket(shared_ptr<TcpSocket>& tsock)
{
	int sock_fd = tsock->get_sock_fd();
	SocksMap::iterator iter = socks_map_.find(sock_fd);
	if(iter == socks_map_.end())
	{
		socks_map_[sock_fd] = tsock;
	}
}

void SocketMgr::RemoveTcpSocket(int sock_fd)
{
	SocksMap::iterator iter = socks_map_.find(sock_fd);
	if(iter != socks_map_.end())
	{
		socks_map_.erase(iter);
	}
}

void SocketMgr::Update()
{
	CheckSocketEvent();
}

void SocketMgr::CheckSocketEvent()
{
	if(!epoller_.WaitForEvent(10))
	{
		return;
	}

	int sock_fd = 0, event_flags = 0;
	while(epoller_.GetSocketEvent(sock_fd, event_flags))
	{
		SocksMap::iterator iter = socks_map_.find(sock_fd);
		if(iter == socks_map_.end())
		{
			continue;
		}
		
		shared_ptr<TcpSocket>& ts = iter->second;
		if(!ts->IsValid() || ts->get_sock_state() == SS_INVALID)
		{
			continue;
		}
		
		if(event_flags & SOCKET_EVENT_ON_EXCEPT)
		{
			//TODO deal with close socket.
			continue;
		}
		
		if(ts->get_sock_state() == SS_LISTENING && (event_flags & SOCKET_EVENT_ON_READ))
		{
			//TODO deal with accept
			continue;
		}

		if(ts->get_sock_state() == SS_CONNECTED && (event_flags & SOCKET_EVENT_ON_READ))
		{
			//TODO deal with read
		}

		if(ts->get_sock_state() == SS_CONNECTED && (event_flags & SOCKET_EVENT_ON_WRITE))
		{
			//TODO deal with write
		}
	}
}
