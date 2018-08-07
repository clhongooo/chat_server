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

	void set_accept_call_back(AcceptCallBack cb) { accept_cb_ = cb; }
	AcceptCallBack get_accept_call_back() { return accept_cb_; }

	bool Listen(int backlog);
	int Accept();

private:
	AcceptCallBack accept_cb_;
};

#endif//TCP_SVR_SOCKET_H_
