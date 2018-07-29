/*************************************************************************
	> File Name: socket.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Fri 06 Jul 2018 02:24:32 PM CST
 ************************************************************************/

#include<socket.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<logging.h>

Socket::Socket()
	: sock_(INVALID_SOCKET)
	, state_(SS_INVALID)
	, remote_ip_(0)
	, remote_port_(0)
{

}

bool Socket::Create(int type, int protocol)
{
	int fd = socket(AF_INET, type, protocol);
	if(fd == -1)
	{
		return false;
	}

	sock_ = fd;
	state_ = SS_CREATED;

	return true;
}

bool Socket::Bind(ipaddr_t ip, port_t port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = ip;
	return bind(sock_, (struct sockaddr*)&addr, sizeof(addr)) == 0;
}

bool Socket::Close()
{
	if(close(sock_) != 0)
	{
		printf("close socket:%d failed\n", sock_);
		return false;
	}
	state_ = SS_CLOSED;
	printf("close socket:%d success.\n", sock_);
	return true;
}

bool Socket::Shutdown(int how)
{
	if(shutdown(sock_, how) != 0)
	{
		return false;
	}

	state_ = SS_CLOSED;
	return true;
}
