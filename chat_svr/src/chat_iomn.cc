/*************************************************************************
	> File Name: chat_iomn.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Mon 06 Aug 2018 09:37:39 AM CST
 ************************************************************************/

#include<iomn.h>

extern char* g_read_buff;
extern int g_buff_size;

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

void DumpAllConnects()
{

}
