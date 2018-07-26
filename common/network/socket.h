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

	int get_sock_fd() const { return sock_; }
	void set_sock_fd(int fd) { sock_ = fd; }
	int get_sock_state() const { return state_; }
	void set_sock_state(int state) { state_ = state; }
	void set_remote_ip(ipaddr_t ip) { remote_ip_ = ip; }
	ipaddr_t get_remote_ip() const { return remote_ip_; }
	void set_remote_port(port_t port) { remote_port_ = port; }
	port_t get_remote_port() const {return remote_port_; }

	bool IsValid() { return state_ != SS_INVALID; }
	bool Create(int type, int protocol);
	bool Bind(ipaddr_t ip, port_t port);
	bool Close();
	bool Shutdown(int how);

private:
	int sock_;
	int state_;
	ipaddr_t remote_ip_;
	port_t remote_port_;
};

#endif//SOCKET_H_
