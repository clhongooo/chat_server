/***************************************************************************
	> File Name: robot_define.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:58:26 PM CST
 ************************************************************************/
#ifndef ROBOT_DEFINE_H_
#define ROBOT_DEFINE_H_

#include<iostream>
#include<map>
#include<memory>

using namespace std;

class Robot;
#define CHAT_SVR_IP "127.0.0.1"
#define CHAT_SVR_PORT 5000

typedef map<int, shared_ptr<Robot>> RobotsMap;

#define ROBOT_SVR_NAME "@iomn_robotsvr"

#endif//ROBOT_DEFINE_H_
