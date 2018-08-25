cc_binary(
    name = "chat_cli",
    srcs = [
        'main.cc',
        'chat_cli_cfg.cc',
        'chat_cli.cc',
        'chat_cli_iomn.cc',
    ],
    incs = [
        '../../common/config',
        '../../thirdparty/glog/src/glog',
        '../../common/network',
        '../../common/head',
        '../../common/iomn',
        '../../build64_release/proto',
    ],
    deps = [
        '//common/config:config',
        '//thirdparty/glog/src:glog',
        '//common/network:network',
        '//common/head:head',
        '//common/iomn:iomn',
        '//proto:base_proto',
    ],
)
