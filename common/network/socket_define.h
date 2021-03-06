/***************************************************************************
	> File Name: socket_define.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Fri 06 Jul 2018 03:18:34 PM CST
 ************************************************************************/
#ifndef SOCKET_DEFINE_H_
#define SOCKET_DEFINE_H_

#include<iostream>
#include<map>
#include<memory>
#include<vector>
#include<sys/epoll.h>
#include<functional>

using namespace std;
class TcpSocket;

typedef unsigned long ipaddr_t;
typedef unsigned short port_t;

#define MAX_RECV_BUF_LEN 1024
#define MAX_SND_BUF_LEN 1024
#define MAX_PKG_LEN	256

#define INVALID_SOCKET -1

#define SOCKET_EVENT_ON_READ 1
#define SOCKET_EVENT_ON_WRITE 2
#define SOCKET_EVENT_ON_EXCEPT 0x100000

#define INIT_EVENT_VEC_SIZE 16 

enum SocketState
{
	SS_INVALID = 0,
	SS_CLOSED = SS_INVALID,
	SS_CREATED,
	SS_CONNECTED,
	SS_ACCEPTED = SS_CONNECTED,
	SS_LISTENING,
};

enum SocketError
{
	SERROR_OK					=	0,
	SERROR_SND_BUF_NULL			=	-1,
	SERROR_PKG_TOO_BIG			=	-2,
	SERROR_SND_FAILED			=	-3,
	SERROR_SOCKET_STATE_ERROR	=	-4,
	SERROR_RCV_TOO_SMALL		=	-5,
};

typedef map<int, shared_ptr<TcpSocket>> SocksMap;

typedef vector<epoll_event> EventVec;

typedef function<void(char*, int)> ReadCallBack;
typedef function<void()> WriteCallBack;
typedef function<void()> CloseCallBack;
typedef function<void()> AcceptCallBack;

#endif//SOCKET_DEFINE_H_
