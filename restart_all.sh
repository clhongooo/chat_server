#########################################################################
# File Name: restart_all.sh
# Author: clhongooo
# mail: clhongooo@163.com
# Created Time: Thu 26 Jul 2018 10:22:33 AM CST
#########################################################################
#!/bin/bash
killall -9 chat_svr
killall -9 robot_svr

cd chat_svr/bin
./chat_svr -log_dir=../log
cd ../../

cd robot/bin
./robot_svr -log_dir=../log
cd ../../

