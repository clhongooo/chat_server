/*************************************************************************
	> File Name: tcp_cli_socket.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 10 Jul 2018 05:19:50 PM CST
 ************************************************************************/

#include "tcp_cli_socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

bool TcpCliSocket::Connect(const char* str_ip, port_t port)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(str_ip);

	if(connect(get_sock_fd(), (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return false;
	}
	set_sock_state(SS_CONNECTED);
	return true;
}
