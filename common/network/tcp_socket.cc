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
