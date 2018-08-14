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
        '../../thirdparty/glog/src',
        '../../common/network',
        '../../common/iomn',
        '../../build64_release/proto',
        '../../common/head',
    ],
    deps = [
        '//thirdparty/glog/src:glog',
        '//common/network:network',
        '//common/iomn:iomn',
        '//common/head:head',
        '//proto:base_proto',
    ],
)
