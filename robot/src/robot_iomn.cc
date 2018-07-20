/*************************************************************************
	> File Name: robot_iomn.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Thu 19 Jul 2018 05:27:05 PM CST
 ************************************************************************/

#include<iomn.h>
#include<stdlib.h>
#include<robot_mgr.h>

extern char* g_read_buffer;
extern int g_buff_size;

void TopIomnMenu();
void PrintTopMenuHelp();
void DumpCreateRobot();
void DumpDisCloseRobot();

void PrintTopMenuHelp()
{
	iomn_push("Available Commands are:\n");
	iomn_push("c) create robot\n");
	iomn_push("d) disclose robot\n");

	iomn_push("q) Quit\n");
	iomn_print("Input your select:\n");
}

void TopIomnMenu()
{
	iomn_push("Welcome to IOMN of Robot Server\n");

	PrintTopMenuHelp();

	while(1)
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
			case 'c':
				DumpCreateRobot();
				break;
			case 'd':
				DumpDisCloseRobot();
				break;
			default:
				break;
		}

		PrintTopMenuHelp();
	}
}

void DumpCreateRobot()
{
	iomn_print("Input number to create robot:");
	
	char *cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;

	int count = atoi(cmd);
	if(count <= 0) return;

	for(int i = 0; i < count; i++)
	{
		if(RobotMgr::Instance().CreateARobot())
		{
			iomn_print("create %d robot success!", i);
		}
		else
		{
			iomn_print("create %d robot failed!", i);
		}
	}
}

void DumpDisCloseRobot()
{
	iomn_print("Close all robots");
	RobotMgr::Instance().CloseAllRobots();
}
