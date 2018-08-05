// -*- mode: c++ -*-
// buffer for TCP read and write
// @author: Ellery Wang
// @date: 2018.08.05
#pragma once

#define MAX_BUFFER 65535

class TcpSocket;
int buf_alloc(int sockfd, unsigned int size);
void settcpsocket(int sockfd, TcpSocket *ts);
int handle_read(int sockfd);
int handle_write(int sockfd);
void send_data(int sockfd, char *data, int len);

void sock_onread(int sockfd, char *data, int len);
void buf_free(int sockfd);
