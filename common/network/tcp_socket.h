/***************************************************************************
	> File Name: tcp_socket.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Fri 06 Jul 2018 03:50:00 PM CST
 ************************************************************************/
#ifndef TCP_SOCKET_H_
#define TCP_SOCKET_H_

#include<socket.h>
#include<memory>

class TcpSocket : public Socket
{
public:
	TcpSocket();
	TcpSocket(const TcpSocket& sock);
	TcpSocket& operator=(const TcpSocket& sock);
	virtual ~TcpSocket() {}

	int Recv();
	void RemovePkg(int pkg_len);
	int Send(const char* buf, int len);

private:
	char rcv_buf_[MAX_RCV_BUF_LEN];	
	int rcv_start_;
	int rcv_bytes_len_;
	
	char snd_buf_[MAX_SND_BUF_LEN];
	int cur_snd_size_;
};

#endif//TCP_SOCKET_H_
