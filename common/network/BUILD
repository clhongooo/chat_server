cc_library(
    name = "network",
    srcs = [
        'socket.cc',
        'tcp_socket.cc',
        'tcp_svr_socket.cc',
        'tcp_cli_socket.cc',
        'socket_mgr.cc',
        'epoller.cc',
        'buffer.cc'
    ],
    incs = [
        '.',
        '../../thirdparty/glog/src/glog',
        '../../thirdparty/glog/src',
    ],
    deps = [
        '//thirdparty/glog/src:glog'
    ],
)
