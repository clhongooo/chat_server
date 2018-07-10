/*************************************************************************
	> File Name: main.cpp
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Tue 03 Jul 2018 04:12:51 PM CST
 ************************************************************************/
#include <sys/ptrace.h>
//#include <libunwind.h>
#include <libunwind-x86_64.h>
#include <libunwind-ptrace.h>

#include<iostream>
#include<logging.h>

using namespace std;

int main()
{
	cout << "hello world!\n";
	google::InitGoogleLogging("chat_svr_log");
	LOG(INFO) << "test glog!";
	return 0;
}
