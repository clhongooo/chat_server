/*************************************************************************
	> File Name: tcp_socket.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Fri 06 Jul 2018 03:50:07 PM CST
 ************************************************************************/

#include <tcp_socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "socket_define.h"

TcpSocket::TcpSocket()
{
	send_buf_ = new char[MAX_SND_BUF_LEN];
	cur_snd_idx_ = 0;
	
	recv_buf_ = new char[MAX_RECV_BUF_LEN];
	recv_start_ = 0;
	recv_bytes_ = 0;
}

TcpSocket::~TcpSocket()
{
	delete[] send_buf_;
	delete[] recv_buf_;
}

int TcpSocket::SendPackage(char* data, int  len)
{
	if(IsValid() == false)
	{
		return SERROR_SOCKET_STATE_ERROR;
	}

	if(len > MAX_PKG_LEN)
	{
		return SERROR_PKG_TOO_BIG;
	}

	if(cur_snd_idx_ + len > MAX_SND_BUF_LEN)
	{
		int err = SendCache();
		if(err < 0)
		{
			return err;
		}

		int n = send(get_sock_fd(), data, len, 0);
		if(n == -1)
		{
			return SERROR_SND_FAILED;
		}
	}
	else
	{
		AddSendCache(data, len);		
	}

	return SERROR_OK;
}

int TcpSocket::SendCache()
{
	if(cur_snd_idx_ == 0)
	{
		return SERROR_SND_BUF_NULL;
	}
	int n = send(get_sock_fd(), send_buf_, cur_snd_idx_, 0);
	if(n == -1)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return SERROR_SND_FAILED;
	}
	cur_snd_idx_ = 0;
	return SERROR_OK;
}

void TcpSocket::AddSendCache(char* data, int len)
{
	if(cur_snd_idx_ + len > MAX_SND_BUF_LEN)
	{
		return;
	}
	memcpy(send_buf_ + cur_snd_idx_, data, len);
	cur_snd_idx_ += len;
}

int TcpSocket::Receive()
{
	if(recv_start_ + recv_bytes_ > MAX_RECV_BUF_LEN)
	{
		return SERROR_RCV_TOO_SMALL;
	}
	
	int n = recv(get_sock_fd(), recv_buf_ + recv_start_ + recv_bytes_, MAX_RECV_BUF_LEN - (recv_start_ + recv_bytes_), 0);
	if(n < 0)
	{
		fprintf(stderr, "%s\n", strerror(errno));	
	}
	else
	{
		recv_bytes_ += n;
	}

	read_cb_(recv_buf_ + recv_start_, recv_bytes_);
	return SERROR_OK;
}

void TcpSocket::RemoveRecvPkg(int pkg_len)
{
	if(pkg_len == recv_bytes_)
	{
		recv_start_ = 0;
		recv_bytes_ = 0;
		return;
	}

	recv_start_ += pkg_len;
	recv_bytes_ -= pkg_len;

	if(recv_start_ + MAX_PKG_LEN > MAX_RECV_BUF_LEN)
	{
		memmove(recv_buf_, recv_buf_+recv_start_, recv_bytes_);
		recv_start_ = 0;
	}
}
