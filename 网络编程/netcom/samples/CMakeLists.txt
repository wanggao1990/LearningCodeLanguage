cmake_minimum_required(VERSION 3.5.0)

project(samples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/samples)   # 工程顶层目录
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)   # 当前cmakelist.txt目录

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJROOT}/bin/samples) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJROOT}/bin) 



######## udp test
# simple
add_executable(udp_server_1     test_udp/udp_server_1.cpp)
add_executable(udp_client_1     test_udp/udp_client_1.cpp)

add_executable(udp_server       test_udp/udp_server.cpp)
add_executable(udp_client       test_udp/udp_client.cpp)

######## tcp test
# simple
add_executable(tcp_server_simple    test_tcp/tcp_server_simple.cpp)

add_executable(tcp_server           test_tcp/tcp_server.cpp)
add_executable(tcp_client           test_tcp/tcp_client.cpp)
add_executable(tcp_client_2         test_tcp/tcp_client_2.cpp)

######## addr test
# simple
add_executable(addr_cvt             11-addr_cvt/name_addr_cvt.cpp)
add_executable(addr_cvt_sockaddr    11-addr_cvt/test_socketaddr.cpp)

add_executable(addr_get             11-addr_cvt/test_get_address.cpp)


######## IO test
add_executable(io_select            5-test_IO/test_select.cpp)
add_executable(io_poll              5-test_IO/test_poll.cpp)
add_executable(io_epoll             5-test_IO/test_epoll.cpp)

######## sockoption test
add_executable(getoptions           7-sockoptions/getoptions.cpp)
add_executable(setoptions           7-sockoptions/setoptions.cpp)

add_executable(test_keepalive       7-sockoptions/test_keepalive.cpp)

######## 14-advancedIO test
add_executable(14-timeout_sigalarm  14-advancedIO/14-timeout_sigalarm.cpp)
add_executable(14-timeout_select    14-advancedIO/14-timeout_select.cpp)
add_executable(14-timeout_sockopt   14-advancedIO/14-timeout_sockopt.cpp)
add_executable(14-readv_writev      14-advancedIO/14-readv_writev.cpp)
add_executable(14-recvmsg_writemsg  14-advancedIO/14-recvmsg_writemsg.cpp)
add_executable(14-recv_send         14-advancedIO/14-recv_send.cpp)

add_executable(14-ioctl_FIONREAD    14-advancedIO/14-ioctl_FIONREAD.cpp)

######## 16- nonblocking IO test
add_executable(nonblocking_RW       16-nonblockIO/nonblocking_RW.cpp)
add_executable(nonblocking_connect  16-nonblockIO/nonblocking_connect.cpp)
add_executable(nonblocking_accept   16-nonblockIO/nonblocking_accept.cpp)

