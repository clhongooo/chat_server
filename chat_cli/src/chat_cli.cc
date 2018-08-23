/*************************************************************************
	> File Name: chat_cli.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月23日 星期四 17时35分06秒
 ************************************************************************/

#include "chat_cli.h"
#include "logging.h"

namespace google
{
	extern uint32 ParseCommandLineFlags(int* argc, char*** argv, bool remove_flags);
}

ChatClient::ChatClient()
{

}

ChatClient::~ChatClient()
{

}

bool ChatClient::InitChatClient(int argc, char** argv)
{
	if(argc < 3)
	{
		LOG(ERROR) << "parameter's count error!";
		return false;
	}

	cout << argv[1] << "   " << argv[2] << endl;

	//init glog
	google::InitGoogleLogging(argv[1]);
	google::ParseCommandLineFlags(&argc, &argv, false);

	//init config
	if(chat_cli_cfg_.ParseFile(argv[2]) == -1)
	{
		LOG(ERROR) << "parse config file error!";
		return false;
	}
	
	return true;	
}
