/*************************************************************************
	> File Name: chat_iomn.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Mon 06 Aug 2018 09:37:39 AM CST
 ************************************************************************/

#include "iomn.h"
#include <memory>
#include "client_conn.h"
#include "conn_mgr.h"

extern char* g_read_buff;
extern int g_buff_size;
extern char* g_dump_buff;

void TopIomnMenu();
void PrintTopMenuHelp();
void DumpAllConnects();

void TopIomnMenu()
{
	iomn_push("Welcome to IOMN of Chat Server\n");

	PrintTopMenuHelp();

	while(1)
	{
		char* cmd = iomn_gets(g_read_buff, g_buff_size);
		if(cmd == NULL) return;
	
		if(*cmd == 'q')
		{
			iomn_print("Good Bye!\n");
			break;
		}
	
		switch(*cmd)
		{
			case 's':
				DumpAllConnects();
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
	iomn_push("s) show connects\n");

	iomn_push("q) Quit\n");
	iomn_print("Input your select:\n");
}

struct tagPrintClientConn
{
	int operator()(shared_ptr<ClientConn> sp_client_conn)
	{
		int len = sp_client_conn->DumpClientConnInfo(g_dump_buff, g_buff_size);
		iomn_print(len, g_dump_buff);
		return 0;
	}
};

void DumpAllConnects()
{
	iomn_print("list of all connects information:\n");
	tagPrintClientConn tag_print_client_conn;
	ConnMgr::Instance().for_each_client(tag_print_client_conn);
}
