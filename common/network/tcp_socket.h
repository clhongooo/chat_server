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

	void Read();
	void Write();
	void SendData(char *data, int len);
	virtual void OnRead(char *data, int len);

protected:
	void AllocBuffer(int sockfd);
};

#endif//TCP_SOCKET_H_
