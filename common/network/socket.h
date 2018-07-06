/***************************************************************************
	> File Name: socket.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Fri 06 Jul 2018 02:24:27 PM CST
 ************************************************************************/
#ifndef SOCKET_H_
#define SOCKET_H_

#include<socket_define.h>

class Socket
{
public:
	Socket();
	virtual ~Socket() {}

	int get_sock_fd() { return sock_; }
	int get_sock_state() { return state_; }
	void set_sock_state(int state) { state_ = state; }
	void set_remote_ip(ipaddr_t ip) { remote_ip_ = ip; }
	ipaddr_t get_remote_ip() { return remote_ip_; }
	void set_remote_port(port_t port) { remote_port_ = port; }
	port_t get_remote_port() {return remote_port_; }

	bool Create(int type, int protocol);
	bool Bind(ipaddr_t ip, port_t port);

private:
	int sock_;
	int state_;
	ipaddr_t remote_ip_;
	port_t remote_port_;
};

#endif//SOCKET_H_
