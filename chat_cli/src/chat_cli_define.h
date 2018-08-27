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

#endif//CHAT_CLI_DEFINE_H_
