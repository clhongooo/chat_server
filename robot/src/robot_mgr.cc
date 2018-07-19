/*************************************************************************
	> File Name: robot_mgr.cc
	> Author: clhongooo
	> Mail: clhongooo@163.com 
	> Created Time: Thu 19 Jul 2018 03:43:20 PM CST
 ************************************************************************/

#include<robot_mgr.h>
#include<robot.h>

RobotMgr& RobotMgr::Instance()
{
	static RobotMgr robot_mgr;
	return robot_mgr;
}

int RobotMgr::CreateRobots(int robots_num)
{
	int count = 0;
	for(int i = 0; i < robots_num; i++)
	{
		Robot robot;
		if(robot.Connect())
		{
			robots_map_[robot.get_robot_id()] = make_shared<Robot>(robot);
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
	}
}

void RobotMgr::CloseAllRobots()
{
	for(auto item : robots_map_)
	{
		item.second->Close();
	}
}