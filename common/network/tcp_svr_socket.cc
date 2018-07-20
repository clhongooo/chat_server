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
		LOG(INFO) << "socket listen error!";
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
		LOG(INFO) << "socket accpet error!";
		return false;
	}

	TcpSvrSocket tssock;
	tssock.set_sock_fd(conn_fd);
	tssock.set_sock_state(SS_CONNECTED);
	shared_ptr<TcpSocket> sp_sock = make_shared<TcpSvrSocket>(tssock);
	SocketMgr::Instance().InsertTcpSocket(sp_sock);	
	return true;
}

