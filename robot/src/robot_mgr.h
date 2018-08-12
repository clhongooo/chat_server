/***************************************************************************
	> File Name: robot_mgr.h
	> Author: clhongooo
	> Mail: clhongooo@163.com
	> Created Time: Thu 19 Jul 2018 03:43:15 PM CST
 ************************************************************************/
#ifndef ROBOT_MGR_H_
#define ROBOT_MGR_H_

#include "robot_define.h"
#include "robot.h"
#include <sys/time.h>

class RobotMgr
{
public:
	RobotMgr();
	~RobotMgr() {}

	static RobotMgr& Instance();

	bool CreateARobot();
	int CreateRobots(int robots_num);
	void CloseRobot(int robot_id);
	void CloseAllRobots();

	int DumpRobotsInfo(char* buffer, int buff_len);

	template<typename Funcation>
	void for_each_robot(Funcation func)
	{
		for(auto& item : robots_map_)
		{
			func(*(item.second.get()));
		}
	}

	void Update();

private:
	RobotsMap robots_map_;
	struct timeval cur_tv_;
};

#endif//ROBOT_MGR_H_
