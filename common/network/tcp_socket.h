/***************************************************************************
	> File Name: tcp_socket.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Fri 06 Jul 2018 03:50:00 PM CST
 ************************************************************************/
#ifndef TCP_SOCKET_H_
#define TCP_SOCKET_H_

#include<socket.h>

class TcpSocket : public Socket
{
public:
	TcpSocket() {}
	~TcpSocket() {}

	bool Listen(int backlog);
	bool Accept();
	bool Connect(ipaddr_t ip, port_t port);
	int Recv(char* buf, int len);
	int Send(const void* buf, int len);
};

#endif//TCP_SOCKET_H_
