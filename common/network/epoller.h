/***************************************************************************
	> File Name: epoller.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Mon 09 Jul 2018 11:23:43 AM CST
 ************************************************************************/
#ifndef EPOLLER_H_
#define EPOLLER_H_

#include<socket_define.h>

class TcpSocket;

class Epoller
{
public:
	Epoller();
	~Epoller() {}

	/**
	 * \brief register events on the epoll file descriptor.
	 * \param tsock assign socket.
	 * \param event_flags a bit mask of socket event.
	 * \return register successilly or not.
	 */
	bool RegisterEvent(TcpSocket& tsock, int event_flags);
	
	bool UnRegisterEvent(TcpSocket& tsock);
	bool WaitForEvent(int timeout);
	bool GetSocketEvent(int& sock_fd, int& event_flags);

private:
	int epoll_fd_;
	EventVec event_vec_;
	int evt_num_;
	int cur_evt_idx_;
};

#endif//EPOLLER_H_