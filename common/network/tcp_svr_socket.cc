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

int TcpSvrSocket::Accept()
{
	struct sockaddr_in addr;
	socklen_t addr_len;
	int conn_fd = accept(get_sock_fd(), (struct sockaddr*)&addr, &addr_len);
	if(conn_fd == -1)
	{
		return -1;
	}
	
	return conn_fd;
}
