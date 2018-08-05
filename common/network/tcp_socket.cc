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
#include<string.h>
#include<logging.h>

#include "buffer.h"

TcpSocket::TcpSocket()
{

}

TcpSocket::TcpSocket(const TcpSocket& sock)
{

}

TcpSocket& TcpSocket::operator=(const TcpSocket& sock)
{
	return *this;
}

void TcpSocket::AllocBuffer(int sockfd)
{
	buf_alloc(sockfd, MAX_BUFFER);
}

void TcpSocket::SendData(char *data, int len)
{
	send_data(get_sock_fd(), data, len);
}

void TcpSocket::Read()
{
	settcpsocket(get_sock_fd(), this);
	handle_read(get_sock_fd());
}

void TcpSocket::Write()
{
	handle_write(get_sock_fd());
}

void TcpSocket::OnRead(char *data, int len)
{
	// receive data
	printf("recevie data from %d, len = %d\n", get_sock_fd(), len);
}
