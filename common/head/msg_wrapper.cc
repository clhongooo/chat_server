/*************************************************************************
	> File Name: msg_wrapper.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Mon 13 Aug 2018 05:01:48 PM CST
 ************************************************************************/

#include "msg_wrapper.h"
#include <sys/time.h>
#include "msg_head.h"

int MsgWrapper::EncodeComMsg(char* buff, uint32 buff_len, uint32 msg_id, const PBMsg& msg)
{
	timeval tv;
	gettimeofday(&tv, NULL);
	MsgHead msg_head;
	msg_head.set_msg_id(msg_id);
	int pkg_len = msg.ByteSize() + sizeof(MsgHead);
	msg_head.set_msg_len(pkg_len);
	msg_head.set_tv_sec(tv.tv_sec);
	msg_head.set_tv_usec(tv.tv_usec);
	
	int head_len = msg_head.PackToBuffer(buff, buff_len);
	msg.SerializeToArray(buff+head_len, buff_len- head_len);
	return head_len + msg.ByteSize();
}

