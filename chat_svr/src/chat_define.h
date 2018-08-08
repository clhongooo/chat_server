/***************************************************************************
	> File Name: chat_define.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Tue 07 Aug 2018 10:25:51 AM CST
 ************************************************************************/
#ifndef CHAT_DEFINE_H_
#define CHAT_DEFINE_H_

#include <iostream>
#include <memory>
#include <map>

using namespace std;

class ClientConn;
typedef map<int, shared_ptr<ClientConn>> ClientConnsMap;

#define CHAT_SVR_NAME "@iomn_chatsvr"

#endif//CHAT_DEFINE_H_
