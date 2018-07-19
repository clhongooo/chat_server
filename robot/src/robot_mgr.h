/***************************************************************************
	> File Name: robot_mgr.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:43:15 PM CST
 ************************************************************************/
#ifndef ROBOT_MGR_H_
#define ROBOT_MGR_H_

#include<robot_define.h>

class RobotMgr
{
public:
	RobotMgr() {}
	~RobotMgr() {}

	static RobotMgr& Instance();

	int CreateRobots(int robots_num);
	void CloseRobot(int robot_id);
	void CloseAllRobots();

private:
	RobotsMap robots_map_;
};

#endif//ROBOT_MGR_H_
