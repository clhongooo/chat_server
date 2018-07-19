#ifndef _AGAME_IOMN_H_
#define _AGAME_IOMN_H_

#include <pthread.h>

pthread_t IomnStart(const char * socket_name, void (* start_func)(int));

int ListenOnLocalSocket(char * socket_name);

void IomnExit(pthread_t tid);

char *iomn_gets(char * buffer, int len);
void iomn_push(const char * format, ...);
void iomn_print(const char * format, ...);
void iomn_print(int len, const char * buff);
void iomn_flush();

#endif