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

void ProcessSignal()
{
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

int main(int argc, char* argv[])
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

	daemon(1, 1);

	while(true)
	{
		SocketMgr::Instance().Update();
	}

	return 0;
}
