/***************************************************************************
	> File Name: account_info.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: 2018年08月25日 星期六 18时08分08秒
 ************************************************************************/
#ifndef ACCOUNT_INFO_H_
#define ACCOUNT_INFO_H_

#include <odb/core.hxx>
#include <iostream>
#include <string>
using namespace std;

#pragma db object
class AccountInfo
{
public:
	AccountInfo(const string& name, const string& pwd)
		: user_name_(name), user_pwd_(pwd) {}

	const string& user_name() { return user_name_; }
	const string& user_pwd() { return user_pwd_; }

private:
	AccountInfo() {}
	friend class odb::access;

private:
	#pragma db id auto
	unsigned long id_;

	string user_name_;
	string user_pwd_;
};

#endif//ACCOUNT_INFO_H_
