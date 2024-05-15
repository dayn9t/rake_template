cmake_minimum_required(VERSION 3.5)
project(hen)

add_definitions(-DBOOST_ALL_DYN_LINK)
add_definitions(-DBOOST_STACKTRACE_USE_BACKTRACE)

find_package(Boost COMPONENTS program_options regex log log_setup filesystem thread REQUIRED)
find_package(Threads)

link_libraries(backtrace dl)


SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(main)
