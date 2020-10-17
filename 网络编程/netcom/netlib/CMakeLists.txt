cmake_minimum_required(VERSION 3.5.0)

project(netlib)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/lib)   # 工程顶层目录
#set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)   # 当前cmakelist.txt目录


set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_INCLUDE_DIR
    include
    CACHE PATH "Installation directory for header files")


set(NETLIB_SOURCES
    ${PROJECT_SOURCE_DIR}/netlib/utils/Date.cpp
    ${PROJECT_SOURCE_DIR}/netlib/net/InetAddress.cpp 
    ${PROJECT_SOURCE_DIR}/netlib/net/inner/Socket.cpp 
)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/netlib/utils
  ${PROJECT_SOURCE_DIR}/netlib/net
  ${PROJECT_SOURCE_DIR}/netlib/net/inner
)

add_library(${PROJECT_NAME} STATIC ${NETLIB_SOURCES}) 


# add_library(${PROJECT_NAME} STATIC)

# # include directories
# target_include_directories(
#   ${PROJECT_NAME} 
#   PRIVATE ${PROJECT_SOURCE_DIR}
#           ${PROJECT_SOURCE_DIR}/netlib/utils
#           ${PROJECT_SOURCE_DIR}/netlib/net
#           ${PROJECT_SOURCE_DIR}/netlib/net/inner
# )


if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32 Rpcrt4) # wepoll)
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif(WIN32)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME netlib)

