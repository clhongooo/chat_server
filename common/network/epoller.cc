/*************************************************************************
	> File Name: epoller.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Mon 09 Jul 2018 11:23:48 AM CST
 ************************************************************************/

#include<epoller.h>
#include<sys/epoll.h>
#include<tcp_socket.h>
#include<string.h>
#include<socket_define.h>

Epoller::Epoller()
	: epoll_fd_(epoll_create(1024))
	, event_vec_(INIT_EVENT_VEC_SIZE)
	, evt_num_(0)
	, cur_evt_idx_(0)
{

}

bool Epoller::RegisterEvent(shared_ptr<TcpSocket>& spsock, int event_flags)
{
	if(!spsock->IsValid())
	{
		return false;
	}

	struct epoll_event evt;
	memset(&evt, 0, sizeof(evt));

	int sock_fd = spsock->get_sock_fd();
	evt.data.fd = sock_fd;
	evt.events = EPOLLRDHUP;
	evt.data.ptr = spsock.get();
	if(event_flags & SOCKET_EVENT_ON_READ)
	{
		evt.events |= EPOLLIN;
	}
	else if(event_flags & SOCKET_EVENT_ON_WRITE)
	{
		evt.events |= EPOLLOUT;
	}

	if(epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, sock_fd, &evt) == 0)
	{
		return true;
	}

	if(errno == ENOENT)
	{
		if(epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, sock_fd, &evt) < 0)
		{
			return false;
		}
	}

	printf("register successful, epoll_fd:%d, sock_fd:%d\n",epoll_fd_, sock_fd);
	return true;
}

bool Epoller::UnRegisterEvent(shared_ptr<TcpSocket>& spsock)
{
	if(!spsock->IsValid())
	{
		return false;
	}

	struct epoll_event evt;
	memset(&evt, 0, sizeof(evt));

	int sock_fd = spsock->get_sock_fd();
	evt.data.fd = sock_fd;

	if(epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, sock_fd, &evt) < 0)
	{
		return false;
	}
	return true;
}

bool Epoller::WaitForEvent(int timeout)
{
	evt_num_ = epoll_wait(epoll_fd_, &(*event_vec_.begin()), static_cast<int>(event_vec_.size()), timeout);
	if(evt_num_ <= 0)
	{
		return false;
	}

	if(evt_num_ == static_cast<int>(event_vec_.size()))
	{
		event_vec_.resize(evt_num_*2);
	}
	cur_evt_idx_= 0;

	return true;
}

bool Epoller::GetSocketEvent(TcpSocket* tsock, int &event_flags)
{
	if(cur_evt_idx_ >= evt_num_)
	{
		return false;
	}

	epoll_event& evt = event_vec_[cur_evt_idx_];
	cur_evt_idx_ += 1;

	tsock = static_cast<TcpSocket*>(evt.data.ptr);
	if(tsock == NULL)
	{
		return false;
	}

	if(evt.events & (EPOLLERR | EPOLLRDHUP))
	{
		event_flags |= SOCKET_EVENT_ON_EXCEPT;
	}

	if(evt.events & EPOLLIN)
	{
		event_flags |= SOCKET_EVENT_ON_READ;
	}

	if(evt.events & EPOLLOUT)
	{
		event_flags |= SOCKET_EVENT_ON_WRITE;
	}
	return true;
}
