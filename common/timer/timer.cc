/*************************************************************************
	> File Name: timer.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Sat 11 Aug 2018 03:43:41 PM CST
 ************************************************************************/

#include "timer.h"

Timer::Timer()
{
	sev_.sigev_notify = SIGEV_SIGNAL;
	sev_.sigev_signo = SIGRTMIN;
	sev_.sigev_value.sival_ptr = this;
	timer_create(CLOCK_REALTIME, &sev_, &tid_);	
}

void Timer::StartTimer(int micro_sec)
{
	struct itimerspec its;
	its.it_value.tv_sec = micro_sec/1000;
	its.it_value.tv_nsec = (micro_sec%1000)*1000000;
	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;
	timer_settime(tid_, 0, &its, NULL);
}

void Timer::StopTimer()
{
	StartTimer(0);
}

void Timer::CancelTimer()
{
	timer_delete(tid_);
}
