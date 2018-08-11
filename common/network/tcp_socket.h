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
	virtual ~TcpSocket();
	
	void set_read_call_back(ReadCallBack cb) { read_cb_ = cb; }
	ReadCallBack get_read_call_back() { return read_cb_; }
	void set_write_call_back(WriteCallBack cb) { write_cb_ = cb; }
	WriteCallBack get_write_call_back() { return write_cb_; }

	int SendPackage(char* data, int len);
	int SendCache();
	void AddSendCache(char* data, int len);
	int Receive();
	void RemoveRecvPkg(int pkg_len);

private:
	ReadCallBack read_cb_;	
	WriteCallBack write_cb_;

	char* send_buf_;
	int cur_snd_idx_;
	
	char* recv_buf_;
	int recv_start_;
	int recv_bytes_;
};

#endif//TCP_SOCKET_H_
