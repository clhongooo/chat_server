/*************************************************************************
	> File Name: msg_head.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Mon 13 Aug 2018 05:02:38 PM CST
 ************************************************************************/

#include "msg_head.h"
#include "proto_define.h"

int MsgHead::PackToBuffer(void* buffer, const uint32 length) const
{
	uint8 *p = (uint8*)buffer;
	const void* dep = buffer + length;
	int ret;
	checkadd(p, proto_pack(p, dep, msg_len_));
	checkadd(p, proto_pack(p, dep, msg_id_));
	checkadd(p, proto_pack(p, dep, body_len_));
	checkadd(p, proto_pack(p, dep, tv_sec_));
	checkadd(p, proto_pack(p, dep, tv_usec_));
	return (int32)(p-(uint8*)buffer);
}

int MsgHead::UnPackFromBuffer(const void* buffer, const uint32 length)
{
	const uint8* p = (uint8*)buffer;
	const void* sep = buffer + length;
	int ret;
	checkadd(p, proto_unpack(msg_len_, p, sep));
	checkadd(p, proto_unpack(msg_id_, p, sep));
	checkadd(p, proto_unpack(body_len_, p, sep));
	checkadd(p, proto_unpack(tv_sec_, p, sep));
	checkadd(p, proto_unpack(tv_usec_, p, sep));
	return (int32)(p-(uint8*)buffer);
}
