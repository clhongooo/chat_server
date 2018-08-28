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
#include "msg_wrapper.h"
#include "account.pb.h"
#include "chat_cli_define.h"

extern STWait stwait;

namespace google
{
	extern uint32 ParseCommandLineFlags(int* argc, char*** argv, bool remove_flags);
}

ChatClient::ChatClient()
	: sp_tcsock_(shared_ptr<TcpSocket>(new TcpCliSocket))
	, state_(false)
{
	gettimeofday(&cur_tv_, NULL);
}

ChatClient::~ChatClient()
{

}

ChatClient& ChatClient::Instance()
{
	static ChatClient inst;
	return inst;
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

	//init socket manager
	if(SocketMgr::Instance().InitSocketMgr() == false)
	{
		LOG(ERROR) << "socket manager init error!";
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

void ChatClient::SendPackage(uint32 msg_id, const PBMsg& msg, bool flag)
{
	if(!sp_tcsock_->IsValid())
	{
		return;
	}

	char* buffer = new char[10*1024];
	int msg_len = MsgWrapper::EncodeComMsg(buffer, 10*1024, msg_id, msg);
	sp_tcsock_->SendPackage(buffer, msg_len, flag);
	delete[] buffer;
}

void ChatClient::ReadPackage(char* data, int len)
{
	uint32 msg_id = 0;
	int head_len = MsgWrapper::DecodeMsgHead(data, len, msg_id);
	
	switch(msg_id)
	{
		case Pb::CS_CMD_RES_ACCOUNT_REGISTER:
			OnResAccountRegister(data+head_len, len-head_len);
			break;
		case Pb::CS_CMD_RES_ACCOUNT_LOGIN:
			OnResAccountLogin(data+head_len, len-head_len);
			break;
		case Pb::CS_CMD_RES_ACCOUNT_LOGOUT:
			OnResAccountLogout();
			break;
		default:
			break;
	}
	
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

	SocketMgr::Instance().Update();	
}

/******************** send request ****************************************/

void ChatClient::OnReqAccountRegister(const char* acc, const char* pwd)
{
	CHECK_WHEN_REQUEST;
	
	Pb::CSReqAccountRegister pkg;
	pkg.set_user_name(acc);
	pkg.set_user_pwd(pwd);
	SendPackage(Pb::CS_CMD_REQ_ACCOUNT_REGISTER, pkg);

	LOCK_WAIT;
}

void ChatClient::OnReqAccountLogin(const char* acc, const char* pwd)
{
	CHECK_WHEN_REQUEST;
	
	Pb::CSReqAccountLogin pkg;
	pkg.set_user_name(acc);
	pkg.set_user_pwd(pwd);
	SendPackage(Pb::CS_CMD_REQ_ACCOUNT_LOGIN, pkg);

	LOCK_WAIT;
}

void ChatClient::OnReqAccountLogout()
{
	CHECK_WHEN_REQUEST;
	
	Pb::CSReqAccountLogout pkg;
	SendPackage(Pb::CS_CMD_REQ_ACCOUNT_LOGOUT, pkg);

	LOCK_WAIT;
}

/********************* deal with the response *****************************/

void ChatClient::OnResAccountRegister(char* data, int len)
{
	Pb::CSResAccountRegister pkg;
	pkg.ParseFromArray(data, len);

	if(pkg.result())
	{
		cout << "register succeed!" << pkg.user_name().c_str() << endl;
	}
	else
	{
		cout << "regsiter failed!" << pkg.user_name().c_str() << endl;
	}
	
	UNLOCK_WAIT;
}

void ChatClient::OnResAccountLogin(char* data, int len)
{
	Pb::CSResAccountLogin pkg;
	pkg.ParseFromArray(data, len);

	if(pkg.result() == 0)
	{
		state_ = true;
		cout << "login succeed!" << pkg.user_name().c_str() << endl;
	}
	else
	{
		cout << "login failed!" << pkg.user_name().c_str() << " errno:" << pkg.result() << endl;
	}
	
	UNLOCK_WAIT;
}

void ChatClient::OnResAccountLogout()
{
	state_ = false;
	
	DisConnect();
	cout << "logout succeed!" << endl;
	UNLOCK_WAIT;
}
