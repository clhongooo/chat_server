/*************************************************************************
	> File Name: tcp_socket.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Fri 06 Jul 2018 03:50:07 PM CST
 ************************************************************************/

#include<tcp_socket.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

bool TcpSocket::Listen(int backlog)
{
	if(listen(get_sock_fd(), backlog) == -1)
	{
		return false;
	}
	set_sock_state(SS_LISTENING);
	return true;
}

bool TcpSocket::Accept()
{
	struct sockaddr_in addr;
	socklen_t addr_len;
	int fd = accept(get_sock_fd(), (struct sockaddr*)&addr, &addr_len);
	if(fd == -1)
	{
		return false;
	}
	
	//TODO new sock
	return true;
}

bool TcpSocket::Connect(ipaddr_t ip, port_t port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = ip;

	if(connect(get_sock_fd(), (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		return false;
	}
	set_sock_state(SS_CONNECTED);
	return true;
}

int TcpSocket::Recv(char* buf, int len)
{
	return recv(get_sock_fd(), buf, len, 0);
}

int TcpSocket::Send(const void* buf, int len)
{
	return send(get_sock_fd(), buf, len, 0);
}
