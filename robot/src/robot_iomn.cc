/*************************************************************************
	> File Name: robot_iomn.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 05:27:05 PM CST
 ************************************************************************/

#include "iomn.h"
#include <stdlib.h>
#include "robot_mgr.h"
#include "robot.h"
#include <string.h>
#include <arpa/inet.h>
#include "msg_test.pb.h"
#include "msg_head.h"
#include "msg_wrapper.h"

extern char* g_read_buff;
extern char* g_dump_buff;
extern int g_buff_size;

void TopIomnMenu();
void PrintTopMenuHelp();
void DumpCreateRobot();
void DumpCloseRobot();
void DumpDisCloseRobot();
void DumpRobotsInfo();
void DumpRobotSendData();

void PrintTopMenuHelp()
{
	iomn_push("Available Commands are:\n");
	iomn_push("c) create robot\n");
	iomn_push("d) disclose robot\n");
	iomn_push("s) show robots\n");
	iomn_push("r) close assigned robot\n");
	iomn_push("n) send data to server\n");

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
			case 's':
				DumpRobotsInfo();
				break;
			case 'r':
				DumpCloseRobot();
				break;
			case 'n':
				DumpRobotSendData();
				break;
			default:
				break;
		}

		PrintTopMenuHelp();
	}
}

void DumpCreateRobot()
{
	iomn_print("Input number to create robot:\n");

	char *cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;

	int count = atoi(cmd);
	if(count <= 0) return;

	for(int i = 0; i < count; i++)
	{
		if(RobotMgr::Instance().CreateARobot())
		{
			iomn_print("create %d robot success!\n", i);
		}
		else
		{
			iomn_print("create %d robot failed!\n", i);
		}
	}
}

struct tagPrintCloseRobot
{
	tagPrintCloseRobot(int robot_id)
	{
		robot_id_ = robot_id;
	}

	int operator()(Robot& robot)
	{
		iomn_print("emmm  %d\n", robot.get_robot_id());
		if(robot_id_ == robot.get_robot_id())
		{
			RobotMgr::Instance().CloseRobot(robot_id_);
			iomn_print("robot[id:%d] closes successfully!\n", robot_id_);
		}
		return 0;
	}
	int robot_id_;
};

void DumpCloseRobot()
{
	iomn_print("Input robot's id which to close:\n");

	char* cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;

	int robot_id = atoi(cmd);
	if(robot_id < 0) return;

	tagPrintCloseRobot print_close_robot(robot_id);
	RobotMgr::Instance().for_each_robot(print_close_robot);
}

void DumpDisCloseRobot()
{
	iomn_print("Close all robots\n");
	RobotMgr::Instance().CloseAllRobots();
}

struct tagPrintRobotInfo
{
	int operator()(Robot& robot)
	{
		int len = robot.DumpRobotInfo(g_dump_buff, g_buff_size);
		iomn_print(len, g_dump_buff);
		return 0;
	}
};

void DumpRobotsInfo()
{
	iomn_print("list of all robot information:\n");
	tagPrintRobotInfo print_robot_info;
	RobotMgr::Instance().for_each_robot(print_robot_info);
}

struct tagPrintRobotSendData
{
	tagPrintRobotSendData(int robot_id)
	{
		robot_id_ = robot_id;
	}

	int operator()(Robot& robot)
	{
		if(robot.get_robot_id() == robot_id_)
		{
			iomn_print("Input the sending data to chat server:\n");
			char* cmd = iomn_gets(g_read_buff, g_buff_size);
			if(cmd == NULL) return -1;
			
			//robot.SendPackage(cmd, strlen(cmd));
		}
		return 0;
	}

	int robot_id_;
};

void DumpRobotSendData()
{
	iomn_print("Input robot's id which to send data:\n");
	char* cmd = iomn_gets(g_read_buff, g_buff_size);
	if(cmd == NULL) return;

	int robot_id = atoi(cmd);
	if(robot_id < 0) return;
	tagPrintRobotSendData print_robot_send_data(robot_id);
	RobotMgr::Instance().for_each_robot(print_robot_send_data);
}
