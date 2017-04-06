add_library (link link.c)
add_library (interface interface.c)
add_library (init init.c server.h)



target_include_directories (link PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories (init PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})