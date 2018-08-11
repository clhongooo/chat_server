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
	sev_.sigev_signo = SIG;
	sev_.sigev_value.sival_ptr = &tid_;
	timer_create(CLOCK_REALTIME, &sev, &tid_);	
}

void Timer::StartTimer(int micro_sec)
{

}

void Timer::StopTimer()
{

}
