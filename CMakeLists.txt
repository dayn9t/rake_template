cmake_minimum_required(VERSION 3.5)
project(hen)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_definitions(-DBOOST_ALL_DYN_LINK)
#set(Boost_USE_STATIC_LIBS ON)
add_definitions(-DBOOST_STACKTRACE_USE_BACKTRACE)

link_libraries(cr_core)

find_package(fmt)
link_libraries(fmt::fmt)

#find_package(Boost COMPONENTS url log log_setup filesystem thread REQUIRED)
find_package(Boost COMPONENTS url REQUIRED)
find_package(Threads)
link_libraries(backtrace dl)

# 海康库路径设置，好像必须在这里设置， 在模块里设置无效
set(PATH_HIK /home/jiang/ws/hik/net)
link_directories(${PATH_HIK}/lib)
include_directories(${PATH_HIK}/include)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(main)
