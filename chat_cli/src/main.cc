/*************************************************************************
	> File Name: main.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月23日 星期四 10时47分15秒
 ************************************************************************/

#include <iostream>
#include "chat_cli.h"
using namespace std;

int main(int argc, char* argv[])
{
	ChatClient client;
	client.InitChatClient(argc, argv);
	return 0;
}
