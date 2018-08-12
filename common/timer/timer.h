/***************************************************************************
	> File Name: timer.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Sat 11 Aug 2018 03:43:36 PM CST
 ************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>
#include <signal.h>

class Timer
{
public:
	Timer();
	virtual ~Timer() {}

	timer_t get_timer_id() { return tid_; }
	struct sigevent get_sev() { return sev_; }

	virtual void TimerEvent() = 0;

	void StartTimer(int micro_sec);
	void StopTimer();
	void CancelTimer();

	static void handler(int sig, siginfo_t *si, void* uc)
	{
		(reinterpret_cast<Timer*>(si->si_value.sival_ptr))->TimerEvent();
	}

private:
	timer_t tid_;
	struct sigevent sev_;
};

#endif//TIMER_H_
