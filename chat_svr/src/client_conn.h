/***************************************************************************
	> File Name: client.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 07 Aug 2018 10:18:01 AM CST
 ************************************************************************/
#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <memory>
#include "tcp_socket.h"
#include "base_type.h"
#include "head_define.h"
using namespace std;

class ClientConn
{
public:
	ClientConn();
	~ClientConn();

	void set_client_id(int id) { client_id_ = id; }
	int get_client_id() { return client_id_; }
	void set_spsock(shared_ptr<TcpSocket> spsock) { spt_sock_ = spsock; }
	shared_ptr<TcpSocket> get_spsock() { return spt_sock_; }

	void CloseClientConn();
	void ReadPackage(char* data, int len);
	void SendPackage(uint32 msg_id, const PBMsg& msg);

	int DumpClientConnInfo(char* buffer, int buff_len);

private:
	shared_ptr<TcpSocket> spt_sock_;
	int client_id_;
};

#endif//CLIENT_H_
