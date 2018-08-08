#########################################################################
# File Name: restart_all.sh
# Author: clhongooo
# mail: clhongooo@163.com
# Created Time: Thu 26 Jul 2018 10:22:33 AM CST
#########################################################################
#!/bin/bash
killall -9 robot_svr_debug
killall -9 chat_svr_debug

cd chat_svr/bin
./chat_svr_debug -log_dir=../log
cd ../../

cd robot/bin
./robot_svr_debug -log_dir=../log
cd ../../

