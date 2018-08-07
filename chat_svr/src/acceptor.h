/***************************************************************************
	> File Name: accpetor.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 07 Aug 2018 05:10:40 PM CST
 ************************************************************************/
#ifndef ACCPETOR_H_
#define ACCPETOR_H_

#include <iostream>
#include <memory>
#include "tcp_socket.h"
using namespace std;

class Acceptor
{
public:
	Acceptor();
	~Acceptor();

	void InitAcceptor();
	void Accept();
	void CreateClientConn(int conn_fd);

private:
	shared_ptr<TcpSocket> sp_tsock_;
};

#endif//ACCPETOR_H_
