
set(PATH_HIK /home/jiang/ws/hik/net) # 海康库路径

link_directories(${PATH_HIK}/lib)
include_directories(${PATH_HIK}/include)



link_libraries(${Boost_LIBRARIES})
link_libraries(${CMAKE_THREAD_LIBS_INIT})

link_libraries(HCCore)

cx_add_mod(hen_net hen)
