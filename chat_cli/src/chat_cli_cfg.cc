/*************************************************************************
	> File Name: chat_cli_cfg.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月23日 星期四 15时58分15秒
 ************************************************************************/

#include "chat_cli_cfg.h"
#include "logging.h"

ChatCliCfg::ChatCliCfg()
	: svr_ip_("")
	, svr_port_(0)
{

}

ChatCliCfg::~ChatCliCfg()
{

}

int ChatCliCfg::ParseFile(const char* file_name)
{
	if(Config::ParseFile(file_name) != -1)
	{
		if(GetValueAsString("chat_svr_ip", svr_ip_) == false)
		{
			LOG(ERROR) << "parse file error! chat_svr_ip";
			return -1;
		}
		if(GetValueAsInt("chat_svr_port", svr_port_) == false)
		{
			LOG(ERROR) << "parse file error! chat_svr_port";
			return -1;
		}
		return 0;
	}

	return -1;
}
