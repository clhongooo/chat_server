/***************************************************************************
	> File Name: chat_cli_define.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月27日 星期一 22时39分57秒
 ************************************************************************/
#ifndef CHAT_CLI_DEFINE_H_
#define CHAT_CLI_DEFINE_H_

#include <pthread.h>

struct STWait{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	bool wait;
};

#define CHECK_WHEN_REQUEST \
	if(stwait.wait) \
	{ \
		LOG(ERROR) << "there is a request that has no response"; \
		return; \
	}

#define LOCK_WAIT \
	pthread_mutex_lock(&stwait.mutex); \
	stwait.wait = true; \
	pthread_mutex_unlock(&stwait.mutex);

#define UNLOCK_WAIT \
	if(stwait.wait) \
	{ \
		pthread_mutex_lock(&stwait.mutex); \
		stwait.wait = false; \
		pthread_cond_signal(&stwait.cond); \
		pthread_mutex_unlock(&stwait.mutex); \
	}

#define BUSY_WAIT \
		pthread_mutex_lock(&stwait.mutex); \
		while(stwait.wait) \
		{ \
			pthread_cond_wait(&stwait.cond, &stwait.mutex); \
		} \
		pthread_mutex_unlock(&stwait.mutex);

#endif//CHAT_CLI_DEFINE_H_
