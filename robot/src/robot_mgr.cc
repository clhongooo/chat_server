/*************************************************************************
	> File Name: robot_mgr.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:43:20 PM CST
 ************************************************************************/

#include<robot_mgr.h>
#include<robot.h>
#include<memory>

RobotMgr::RobotMgr()
{
	gettimeofday(&cur_tv_, NULL);
}

RobotMgr& RobotMgr::Instance()
{
	static RobotMgr robot_mgr;
	return robot_mgr;
}

bool RobotMgr::CreateARobot()
{
	shared_ptr<Robot> sprobot = shared_ptr<Robot>(new Robot);
	if(sprobot->Connect())
	{
		lock_guard<mutex> guard(robots_map_mutex_);
		robots_map_[sprobot->get_robot_id()] = sprobot;
		return true;
	}
	return false;
}

int RobotMgr::CreateRobots(int robots_num)
{
	int count = 0;
	for(int i = 0; i < robots_num; i++)
	{
		shared_ptr<Robot> sprobot = shared_ptr<Robot>(new Robot);
		if(sprobot->Connect())
		{
			lock_guard<mutex> guard(robots_map_mutex_);
			robots_map_[sprobot->get_robot_id()] = sprobot;
			count++;
		}
	}
	return count;
}

void RobotMgr::CloseRobot(int robot_id)
{
	RobotsMap::iterator iter = robots_map_.find(robot_id);
	if(iter != robots_map_.end())
	{	
		iter->second->Close();
		lock_guard<mutex> guard(robots_map_mutex_);
		robots_map_.erase(iter);
	}
}

void RobotMgr::CloseAllRobots()
{
	for(auto& item : robots_map_)
	{
		item.second->Close();
	}
		
	lock_guard<mutex> guard(robots_map_mutex_);
	robots_map_.clear();
}

int RobotMgr::DumpRobotsInfo(char* buffer, int buff_len)
{
	int len = 0;
	for(auto& item : robots_map_)
	{
		len += item.second->DumpRobotInfo(buffer+len, buff_len-len);
	}
	return len;
}

struct tagUpdateSendCache
{
	int operator()(Robot& robot)
	{
		robot.get_tsock().SendCache();
		return 0;
	}
};

void RobotMgr::Update()
{
	struct timeval now_tv;
	gettimeofday(&now_tv, NULL);
	int now_tv_msec = now_tv.tv_sec*1000 + now_tv.tv_usec/1000;
	int last_tv_msec = cur_tv_.tv_sec*1000 + cur_tv_.tv_usec/1000;
	
	if(now_tv_msec - last_tv_msec >= 20)
	{
		tagUpdateSendCache tag_send_cache;
		for_each_robot(tag_send_cache);
	}
}
