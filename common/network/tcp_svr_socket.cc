/*************************************************************************
	> File Name: tcp_svr_socket.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 10 Jul 2018 05:19:38 PM CST
 ************************************************************************/

#include<tcp_svr_socket.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<socket_mgr.h>
#include<logging.h>

bool TcpSvrSocket::Listen(int backlog)
{
	if(listen(get_sock_fd(), backlog) == -1)
	{
		return false;
	}
	set_sock_state(SS_LISTENING);
	return true;
}

bool TcpSvrSocket::Accept()
{
	struct sockaddr_in addr;
	socklen_t addr_len;
	int conn_fd = accept(get_sock_fd(), (struct sockaddr*)&addr, &addr_len);
	if(conn_fd == -1)
	{
		return false;
	}

	shared_ptr<TcpSocket> sp_sock = shared_ptr<TcpSocket>(new TcpSvrSocket);
	sp_sock->set_sock_fd(conn_fd);
	sp_sock->set_sock_state(SS_CONNECTED);
	SocketMgr::Instance().InsertTcpSocket(sp_sock, SOCKET_EVENT_ON_READ | SOCKET_EVENT_ON_WRITE);

	AllocBuffer(conn_fd);
	return true;
}
