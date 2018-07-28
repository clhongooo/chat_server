/*************************************************************************
	> File Name: main.cpp
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 03 Jul 2018 04:12:51 PM CST
 ************************************************************************/
#include<logging.h>
#include<tcp_svr_socket.h>
#include<netinet/in.h>
#include<memory>
#include<socket_mgr.h>
#include<unistd.h>
#include<signal.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void ProcessSignal()
{
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

namespace google {
extern uint32 ParseCommandLineFlags(int* argc, char*** argv, bool remove_flags);
}

int oldmain(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc, &argv, true);

	ProcessSignal();

	LOG(INFO) << "chat server start";
	TcpSvrSocket tssock;
	tssock.Create(SOCK_STREAM, 0);
	tssock.Bind(INADDR_ANY, 5000);
	tssock.Listen(5000);

	shared_ptr<TcpSocket> sp_sock = make_shared<TcpSvrSocket>(tssock);
	SocketMgr::Instance().InsertTcpSocket(sp_sock, SOCKET_EVENT_ON_READ);

	// daemon(1, 1);

	while(true)
	{
		SocketMgr::Instance().Update();
	}

	return 0;
}

#define MAX_EVENTS 10
#define MAXLINE 10

void setnonblocking(int sock)
{
	int opts;
	opts = fcntl(sock, F_GETFL);

	if(opts < 0) {
		perror("fcntl(sock, GETFL)");
		exit(1);
	}

	opts = opts | O_NONBLOCK;

	if(fcntl(sock, F_SETFL, opts) < 0) {
		perror("fcntl(sock, SETFL, opts)");
		exit(1);
	}
}

int main(int argc, char* argv[])
{
	printf("chat server start\n");
	struct epoll_event ev, events[MAX_EVENTS];
	int listen_sock, conn_sock, nfds, epfd, n, sockfd;
	socklen_t addrlen;
	char line[1024];

	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_sock == -1) {
		fprintf(stderr, "%s\n", strerror(errno));
		exit(-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(listen_sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
	    fprintf(stderr, "%s\n", strerror(errno));
		exit(-1);
	}

	if (listen(listen_sock, 5000) == -1) {
	    fprintf(stderr, "%s\n", strerror(errno));
		exit(-1);
	}

	epfd = epoll_create1(0);
	if (epfd == -1) {
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < nfds; ++i) {
			if (events[i].data.fd == listen_sock) {
				printf("accept connection, fd is %d\n", listen_sock);
				conn_sock = accept(listen_sock,
								   (struct sockaddr *) &addr, &addrlen);
				if (conn_sock == -1) {
					perror("accept");
					exit(EXIT_FAILURE);
				}
				setnonblocking(conn_sock);
				char *str = inet_ntoa(addr.sin_addr);
				printf("connect from %s\n", str);

				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, conn_sock,
							  &ev) == -1) {
					perror("epoll_ctl: conn_sock");
					exit(EXIT_FAILURE);
				}
			}
			else if(events[i].events & EPOLLIN) {
				if((sockfd = events[i].data.fd) < 0)
					continue;

				if((n = read(sockfd, line, MAXLINE)) < 0) {
					if(errno == ECONNRESET) {
						close(sockfd);
						events[i].data.fd = -1;
					} else {
						printf("readline error");
					}
				} else if(n == 0) {
					close(sockfd);
					events[i].data.fd = -1;
				}

				printf("received data: %s\n", line);

				ev.data.fd = sockfd;
				ev.events = EPOLLOUT | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
			else if(events[i].events & EPOLLOUT) {
				sockfd = events[i].data.fd;
				write(sockfd, line, 100);

				printf("written data: %s\n", line);

				ev.data.fd = sockfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
			}
		}
	}

	return 0;
}
