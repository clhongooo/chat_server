/*************************************************************************
	> File Name: chat_cli_iomn.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: 2018年08月23日 星期四 20时20分04秒
 ************************************************************************/

#include "iomn.h"
#include <string.h>
#include "chat_cli.h"
#include "chat_cli_define.h"

extern char* g_read_buff;
extern int g_buff_size;
extern STWait stwait;

/*******************  declare function *********************/
void TopIomnMenu();
void PrintTopMenuHelp();

void AccMgrMenuHelp();
void PrintAccMgrMenuHelp();
void DumpAccMgrRegisterInfo();
void DumpAccMgrLoginInfo();

void AccOnlineMenuHelp();
void PrintAccOnlineMenuHelp();


/******************** implemention *************************/

void TopIomnMenu()
{
	iomn_push("Welcome to IOMN of Client Server\n");

	PrintTopMenuHelp();

	while(true)
	{
		char* cmd = iomn_gets(g_read_buff, g_buff_size);
		if(cmd == NULL) break;

		if(*cmd == 'q')
		{
			iomn_print("Good Bye!\n");
			break;
		}

		switch(*cmd)
		{
			case 'l':
				AccMgrMenuHelp();
				break;
			default:
				break;
		}

		PrintTopMenuHelp();
	}
}

void PrintTopMenuHelp()
{
	iomn_push("Available Commands are:\n");
	iomn_push("l) login or register\n");
	
	iomn_push("q) Quit\n");
	iomn_print("Input your select:\n");
}

/********************* account manager **********************/
void AccMgrMenuHelp()
{
	PrintAccMgrMenuHelp();

	while(true)
	{
		char* cmd = iomn_gets(g_read_buff, g_buff_size);
		if(cmd == NULL) break;

		if(*cmd == 'q')
		{
			iomn_print("Back to the top menu!\n");
			return;
		}

		switch(*cmd)
		{
			case 'r':
				DumpAccMgrRegisterInfo();
				break;
			case 'l':
				DumpAccMgrLoginInfo();
				break;
			default:
				break;
		}

		BUSY_WAIT;
		
		if(ChatClient::Instance().get_state() == false)
		{
			PrintAccMgrMenuHelp();
		}
		else
		{
			AccOnlineMenuHelp();
		}
	}
}

void PrintAccMgrMenuHelp()
{
	iomn_push("Account Manager Available Commands are:\n");
	iomn_push("r) register a new account\n");
	iomn_push("l) account login\n");
	iomn_push("q) Back to upper menu\n");
	
	iomn_print("Input your select:\n");
}

void DumpAccMgrRegisterInfo()
{
	iomn_print("Input new account:\n");

	char* cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;
	char acc[256] = {0};
	int cmd_len = strlen(cmd);
	strncpy(acc, cmd, cmd_len-1);

	iomn_print("Input the password:\n");
	cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;
	char pwd[256] = {0};
	cmd_len = strlen(cmd);
	strncpy(pwd, cmd, cmd_len-1);

	iomn_print("Input the confirmed password:\n");
	cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;
	char repwd[256] = {0};
	cmd_len = strlen(cmd);
	strncpy(repwd, cmd, cmd_len-1);

	if(strcmp(pwd, repwd) != 0)
	{
		iomn_print("password is not match with confirmed password\n");
		return;
	}

	ChatClient::Instance().OnReqAccountRegister(acc, pwd);
}

void DumpAccMgrLoginInfo()
{
	iomn_print("Input account:\n");
	char* cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;
	char acc[256] = {0};
	int cmd_len = strlen(cmd);
	strncpy(acc, cmd, cmd_len-1);

	iomn_print("Input password:\n");
	cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;
	char pwd[256] = {0};
	cmd_len = strlen(cmd);
	strncpy(pwd, cmd, cmd_len-1);
	
	ChatClient::Instance().OnReqAccountLogin(acc, pwd);
}

/****************** account online *************************************/
void AccOnlineMenuHelp()
{
	PrintAccOnlineMenuHelp();
	
	while(true)
	{
		char* cmd = iomn_gets(g_read_buff, g_buff_size);
		if(cmd == NULL) break;
		
		if(*cmd == 'q')
		{
			iomn_print("Back to upper menu!\n");
			return;
		}

		switch(*cmd)
		{
			case 'o':
				ChatClient::Instance().OnReqAccountLogout();
				break;
			default:
				break;
		}

		BUSY_WAIT;
		
		if(ChatClient::Instance().get_state())
		{
			PrintAccOnlineMenuHelp();
		}
		else
		{
			AccMgrMenuHelp();
		}
	}
}

void PrintAccOnlineMenuHelp()
{
	iomn_push("Account Online Available Commands are:\n");
	iomn_push("o) account logout\n");
	iomn_push("q) Back to upper menu\n");
	
	iomn_print("Input your select:\n");
}
