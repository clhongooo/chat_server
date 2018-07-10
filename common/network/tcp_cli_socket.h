/***************************************************************************
	> File Name: tcp_cli_socket.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 10 Jul 2018 05:19:44 PM CST
 ************************************************************************/
#ifndef TCP_CLI_SOCKET_H_
#define TCP_CLI_SOCKET_H_

#include<tcp_socket.h>

class TcpCliSocket : public TcpSocket
{
public:
	TcpCliSocket() {}
	~TcpCliSocket() {}

	bool Connect(ipaddr_t ip, port_t port);
};

#endif//TCP_CLI_SOCKET_H_
