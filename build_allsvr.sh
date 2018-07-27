#########################################################################
# File Name: build_allsvr.sh
# Author: clhongooo
# mail: clhongooo@163.com
# Created Time: Fri 27 Jul 2018 11:14:31 AM CST
#########################################################################
#!/bin/bash

cd chat_svr/src
blade build -pdebug
cd ../..

cd robot/src
blade build -pdebug
cd ../..

killall -9 chat_svr_debug
killall -9 robot_svr_debug

cd chat_svr/bin
./chat_svr_debug -log_dir=../log
cd ../..

cd robot/bin
./robot_svr_debug -log_dir=../log
cd ../..
