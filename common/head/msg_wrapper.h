/***************************************************************************
	> File Name: msg_wrapper.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Mon 13 Aug 2018 05:01:41 PM CST
 ************************************************************************/
#ifndef MSG_WRAPPER_H_
#define MSG_WRAPPER_H_

#include "head_define.h"
#include "base_type.h"

class MsgWrapper
{
public:
	MsgWrapper() {}
	~MsgWrapper() {}

	int EncodeComMsg(char* buff, uint32 buff_len, uint32 msg_id, const PBMsg& msg);
};

#endif//MSG_WRAPPER_H_
