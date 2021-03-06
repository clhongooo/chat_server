/*************************************************************************
	> File Name: acceptor.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Tue 07 Aug 2018 05:10:58 PM CST
 ************************************************************************/

#include <iostream>
#include "acceptor.h"
#include <memory>
#include "tcp_socket.h"
#include "tcp_svr_socket.h"
#include <functional>
#include "socket_define.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include "socket_mgr.h"
#include "client_conn.h"
#include "conn_mgr.h"
#include "logging.h"

Acceptor::Acceptor()
{
	
}

Acceptor::~Acceptor()
{
	
}

bool Acceptor::InitAcceptor()
{
	sp_tsock_ = shared_ptr<TcpSocket>(new TcpSvrSocket);
	sp_tsock_->Create(SOCK_STREAM, 0);
	sp_tsock_->Bind(INADDR_ANY, 5000);
	
	TcpSvrSocket* tssock = static_cast<TcpSvrSocket*>(sp_tsock_.get());
	if(tssock)
	{
		AcceptCallBack cb = std::bind(&Acceptor::Accept, this);
		tssock->set_accept_call_back(cb);
		
		if(tssock->Listen(1000) == false)
		{
			LOG(ERROR) << "chat server's acceptor listen error";
			return false;
		}
	}
	else
	{
		LOG(ERROR) << "server inner error";
		return false;
	}

	SocketMgr::Instance().RegisterSocketEvent(sp_tsock_, SOCKET_EVENT_ON_READ);

	return true;
}

void Acceptor::Accept()
{
	TcpSvrSocket* tssock = static_cast<TcpSvrSocket*>(sp_tsock_.get());
	if(tssock == NULL)
	{
		return;
	}

	int conn_fd = tssock->Accept();
	if(conn_fd == -1)
	{
		LOG(ERROR) << "listener accepts failly!";
		return;
	}

	CreateClientConn(conn_fd);
}

void Acceptor::CreateClientConn(int conn_fd)
{
	shared_ptr<ClientConn> sp_client_conn = shared_ptr<ClientConn>(new ClientConn);
	sp_client_conn->set_client_id(conn_fd);

	shared_ptr<TcpSocket> sp_tsock = shared_ptr<TcpSocket>(new TcpSvrSocket);
	sp_tsock->set_sock_fd(conn_fd);
	sp_tsock->set_sock_state(SS_CONNECTED);
	sp_client_conn->set_spsock(sp_tsock);

	CloseCallBack close_cb = std::bind(&ClientConn::CloseClientConn, sp_client_conn.get());
	sp_tsock->set_close_call_back(close_cb);
	using std::placeholders::_1;
	using std::placeholders::_2;
	ReadCallBack read_cb = std::bind(&ClientConn::ReadPackage, sp_client_conn.get(), _1, _2);
	sp_tsock->set_read_call_back(read_cb);

	SocketMgr::Instance().RegisterSocketEvent(sp_tsock, SOCKET_EVENT_ON_READ | SOCKET_EVENT_ON_WRITE);

	ConnMgr::Instance().InsertConnsMap(sp_client_conn);

	LOG(INFO) << "create new client connect successfully! client id:" << sp_client_conn->get_client_id();
}
