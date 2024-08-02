
link_libraries(hcnetsdk HCCore hpr hen_cppw)

link_libraries(${Boost_LIBRARIES})
link_libraries(${CMAKE_THREAD_LIBS_INIT})

message(STATUS "Current link paths:")
foreach(dir ${CMAKE_MODULE_PATH})
    message(STATUS "          ${dir}")
endforeach()

cx_add_so_mod(hen_ce hen)
add_dependencies(hen_ce hen_cppw)
