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

int main(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::ParseCommandLineFlags(&argc, &argv, true);
	
	LOG(INFO) << "chat server start";
	TcpSvrSocket tssock;
	tssock.Create(SOCK_STREAM, 0);
	tssock.Bind(INADDR_ANY, 5000);
	tssock.Listen(1000);

	shared_ptr<TcpSocket> sp_sock = make_shared<TcpSvrSocket>(tssock);
	SocketMgr::Instance().InsertTcpSocket(sp_sock);

	daemon(1, 1);

	while(true)
	{
		SocketMgr::Instance().Update();
		sleep(1);
	}

	return 0;
}
