/***************************************************************************
	> File Name: tcp_svr_socket.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 10 Jul 2018 05:19:29 PM CST
 ************************************************************************/
#ifndef TCP_SVR_SOCKET_H_
#define TCP_SVR_SOCKET_H_

#include<tcp_socket.h>

class TcpSvrSocket : public TcpSocket
{
public:
	TcpSvrSocket() {}
	~TcpSvrSocket() {}

	bool Listen(int backlog);
	bool Accept();
};

#endif//TCP_SVR_SOCKET_H_
