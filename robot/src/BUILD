cc_binary(
    name = 'robot_svr',
    srcs = [
        'main.cc',
        'robot.cc',
        'robot_mgr.cc',
        'robot_iomn.cc',
    ],
    incs = [
        '.',
        '../../thirdparty/glog/src/glog',
        '../../common/network',
        '../../common/iomn',
    ],
    deps = [
        '//thirdparty/glog/src:glog',
        '//common/network:network',
        '//common/iomn:iomn',
    ],
)
