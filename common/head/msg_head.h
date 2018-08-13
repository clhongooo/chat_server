/***************************************************************************
	> File Name: msg_head.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Mon 13 Aug 2018 05:02:34 PM CST
 ************************************************************************/
#ifndef MSG_HEAD_H_
#define MSG_HEAD_H_

#include "base_type.h"

class MsgHead
{
public:
	MsgHead() : msg_len_(0),msg_id_(0),body_len_(0){}
	~MsgHead() {}
	
	int get_msg_len() { return msg_len_; }
	void set_msg_len(int len) { msg_len_ = len; }
	int get_msg_id() { return msg_id_; }
	void set_msg_id(int id) { msg_id_ = id; }
	int get_body_len() { return body_len_; }
	void set_body_len(int len) { body_len_ = len; }
	int get_tv_sec() { return tv_sec_; }
	void set_tv_sec(int sec) { tv_sec_ = sec; }
	int get_tv_usec() { return tv_usec_; }
	void set_tv_usec(int usec) { tv_usec_ = usec; }

	int PackToBuffer(void* buffer, const uint32 length) const;
	int UnPackFromBuffer(const void * buffer, uint32 length);

private:
	int msg_len_;
	int msg_id_;
	int body_len_;
	int tv_sec_;
	int tv_usec_;
};

#endif//MSG_HEAD_H_
