
link_libraries(hcnetsdk HCCore hpr)

link_libraries(${Boost_LIBRARIES})
link_libraries(${CMAKE_THREAD_LIBS_INIT})

message(STATUS "Current link paths:")
foreach(dir ${CMAKE_MODULE_PATH})
    message(STATUS "          ${dir}")
endforeach()

cx_add_mod(hen_cppw hen)
