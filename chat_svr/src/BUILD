cc_binary(
    name = 'chat_svr',
    srcs = [
        'main.cpp',
        'chat_iomn.cc',
        'acceptor.cc',
        'client_conn.cc',
        'conn_mgr.cc',
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
        '//proto:base_proto',
        '//common/head:head',
    ],
)
