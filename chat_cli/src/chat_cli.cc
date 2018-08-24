/*************************************************************************
	> File Name: chat_cli.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月23日 星期四 17时35分06秒
 ************************************************************************/

#include "chat_cli.h"
#include "logging.h"
#include <sys/socket.h>
#include "socket_define.h"
#include "socket_mgr.h"

namespace google
{
	extern uint32 ParseCommandLineFlags(int* argc, char*** argv, bool remove_flags);
}

ChatClient::ChatClient()
{
	sp_tcsock_ = shared_ptr<TcpSocket>(new TcpCliSocket);
	gettimeofday(&cur_tv_, NULL);
}

ChatClient::~ChatClient()
{

}

bool ChatClient::InitChatClient(int argc, char** argv)
{
	if(argc < 3)
	{
		LOG(ERROR) << "parameter's count error!";
		return false;
	}

	//init glog
	google::InitGoogleLogging(argv[1]);
	google::ParseCommandLineFlags(&argc, &argv, false);

	//init config
	if(chat_cli_cfg_.ParseFile(argv[2]) == -1)
	{
		LOG(ERROR) << "parse config file error!";
		return false;
	}
	
	//init socket and connect to the server
	if(sp_tcsock_->Create(SOCK_STREAM, 0) == false)
	{
		LOG(ERROR) << "socket create error!";
		return false;
	}
	if(sp_tcsock_->IsValid() == false)
	{
		LOG(ERROR) << "socket invalid!";
		return false;
	}
	
	TcpCliSocket* tc_sock = static_cast<TcpCliSocket*>(sp_tcsock_.get());
	if(tc_sock == NULL)
	{
		return false;
	}

	cout << chat_cli_cfg_.get_svr_ip().c_str() << " " << chat_cli_cfg_.get_svr_port() << endl;
 
	if(tc_sock->Connect(chat_cli_cfg_.get_svr_ip().c_str(), chat_cli_cfg_.get_svr_port()) == false)
	{
		LOG(ERROR) << "connect to the server error!";
		return false;
	}
	
	//bind callback function
	CloseCallBack close_cb = std::bind(&ChatClient::DisConnect, this);
	sp_tcsock_->set_close_call_back(close_cb);
	using std::placeholders::_1;
	using std::placeholders::_2;
	ReadCallBack read_cb = std::bind(&ChatClient::ReadPackage, this, _1, _2);
	sp_tcsock_->set_read_call_back(read_cb);
	SocketMgr::Instance().RegisterSocketEvent(sp_tcsock_, SOCKET_EVENT_ON_READ | SOCKET_EVENT_ON_WRITE);

	return true;	
}

bool ChatClient::DisConnect()
{
	if(sp_tcsock_->Close())
	{
		SocketMgr::Instance().UnRegisterSocketEvent(sp_tcsock_);
		return true;
	}
	return false;
}

void ChatClient::ReadPackage(char* data, int len)
{
	sp_tcsock_->RemoveRecvPkg(len);
}

void ChatClient::Update()
{
	struct timeval now_tv;
	gettimeofday(&now_tv, NULL);
	int now_tv_msec = now_tv.tv_sec*1000 + now_tv.tv_usec/1000;
	int last_tv_msec = cur_tv_.tv_sec*1000 + cur_tv_.tv_usec/1000;
	
	if(now_tv_msec - last_tv_msec >= 20)
	{
		sp_tcsock_->SendCache();
	}
}
