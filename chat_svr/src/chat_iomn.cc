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
#include <string.h>

extern char* g_read_buff;
extern int g_buff_size;
extern char* g_dump_buff;

void TopIomnMenu();
void PrintTopMenuHelp();
void DumpAllConnects();
void DumpClientConnSendData();

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
			case 'n':
				DumpClientConnSendData();
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
	iomn_push("n) send data to assign conn\n");

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

struct tagPrintConnSendData
{
	tagPrintConnSendData(int conn_id)
	{
		conn_id_ = conn_id;
	}

	int operator()(shared_ptr<ClientConn> conn)
	{
		if(conn->get_client_id() != conn_id_)
		{
			return -1;
		}
		iomn_print("Input the sending data to the peer robot:\n");
		char* cmd = iomn_gets(g_read_buff, g_buff_size);
		if(cmd == NULL) return -1;
		
		//conn->SendPackage(cmd, strlen(cmd));
		return 0;
	}
	int conn_id_;
};

void DumpClientConnSendData()
{
	iomn_print("Input conn's id which to send data:\n");
	char* cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;

	int conn_id = atoi(cmd);
	if(conn_id < 0) return;
	tagPrintConnSendData print_conn_send_data(conn_id);
	ConnMgr::Instance().for_each_client(print_conn_send_data);
}
