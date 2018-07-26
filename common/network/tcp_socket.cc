/*************************************************************************
	> File Name: tcp_socket.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Fri 06 Jul 2018 03:50:07 PM CST
 ************************************************************************/

#include<tcp_socket.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<logging.h>

TcpSocket::TcpSocket()
	: rcv_start_(0)
	, rcv_bytes_len_(0)
	, cur_snd_size_(0)
{
	bzero(rcv_buf_, MAX_RCV_BUF_LEN);
	bzero(snd_buf_, MAX_SND_BUF_LEN);
}

TcpSocket::TcpSocket(const TcpSocket& sock)
{
	if(this != &sock)
	{
		set_sock_fd(sock.get_sock_fd());
		set_sock_state(sock.get_sock_state());
		set_remote_ip(sock.get_remote_ip());
		set_remote_port(sock.get_remote_port());
		rcv_start_ = sock.rcv_start_;
		rcv_bytes_len_ = sock.rcv_bytes_len_;
		memcpy(rcv_buf_, sock.rcv_buf_, MAX_RCV_BUF_LEN);
		cur_snd_size_ = sock.cur_snd_size_;
		memcpy(snd_buf_, sock.snd_buf_, MAX_SND_BUF_LEN);
	}
}

TcpSocket& TcpSocket::operator=(const TcpSocket& sock)
{
	if(this != &sock)
	{
		set_sock_fd(sock.get_sock_fd());
		set_sock_state(sock.get_sock_state());
		set_remote_ip(sock.get_remote_ip());
		set_remote_port(sock.get_remote_port());
		rcv_start_ = sock.rcv_start_;
		rcv_bytes_len_ = sock.rcv_bytes_len_;
		memcpy(rcv_buf_, sock.rcv_buf_, MAX_RCV_BUF_LEN);
		cur_snd_size_ = sock.cur_snd_size_;
		memcpy(snd_buf_, sock.snd_buf_, MAX_SND_BUF_LEN);
	}
	return *this;
}

int TcpSocket::Recv()
{
	if(get_sock_state() != SS_CONNECTED)
	{
		return SERROR_SOCKET_STATE_ERROR;
	}

	if(rcv_start_ + rcv_bytes_len_ > MAX_RCV_BUF_LEN)
	{
		return SERROR_RCV_TOO_SMALL;
	}

	int rcv_len = recv(get_sock_fd(), rcv_buf_ + rcv_start_ + rcv_bytes_len_, MAX_RCV_BUF_LEN - (rcv_start_ + rcv_bytes_len_), 0);
	if(rcv_len > 0)
	{
		rcv_bytes_len_ += rcv_len;
	}
	return rcv_bytes_len_;
}

void TcpSocket::RemovePkg(int pkg_len)
{
	if(pkg_len > rcv_bytes_len_)
	{
		return;
	}
	
	if(pkg_len == rcv_bytes_len_)
	{
		rcv_start_ = 0;
		rcv_bytes_len_ = 0;
		return;
	}
	
	rcv_start_ += pkg_len;
	rcv_bytes_len_ -= pkg_len;

	if(rcv_start_ + MAX_PKG_LEN > MAX_RCV_BUF_LEN)
	{
		memmove(rcv_buf_, rcv_buf_ + rcv_start_, rcv_bytes_len_);
		rcv_start_ = 0;
	}
}

int TcpSocket::Send(const char* buf, int len)
{
	if(buf == NULL)
	{
		return SERROR_SND_BUF_NULL;
	}

	if(len > MAX_PKG_LEN)
	{
		return SERROR_PKG_TOO_BIG;
	}

	if(get_sock_state() != SS_CONNECTED)
	{
		return SERROR_SOCKET_STATE_ERROR;
	}

	if(cur_snd_size_ + len > MAX_SND_BUF_LEN)
	{
		int snd_size = send(get_sock_fd(), snd_buf_, cur_snd_size_, 0);
		if(snd_size < 0)
		{
			return SERROR_SND_FAILED;
		}
		cur_snd_size_ = 0;

		snd_size = send(get_sock_fd(), buf, len, 0);
		if(snd_size < 0)
		{
			return SERROR_SND_FAILED;
		}

		return snd_size;
	}
	else
	{
		memcpy(snd_buf_ + cur_snd_size_, buf, len);
		cur_snd_size_ += len;
	}

	return SERROR_OK;
}
