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

TcpSocket::TcpSocket(const TcpSocket& sock)
{
	if(this != &sock)
	{
		set_sock_fd(sock.get_sock_fd());
		set_sock_state(sock.get_sock_state());
		set_remote_ip(sock.get_remote_ip());
		set_remote_port(sock.get_remote_port());
	}
}

TcpSocket& TcpSocket::operator=(const TcpSocket& sock)
{
	if(this != &sock)
	{
		set_sock_fd(sock.get_sock_fd());
		set_sock_state(sock.get_sock_state());
		set_remote_ip(sock.get_remote_ip());
		set_remote_port(sock.get_remote_port());
	}
	return *this;
}

int TcpSocket::Recv(char* buf, int len)
{
	return recv(get_sock_fd(), buf, len, 0);
}

int TcpSocket::Send(const void* buf, int len)
{
	return send(get_sock_fd(), buf, len, 0);
}
