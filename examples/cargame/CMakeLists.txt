cmake_minimum_required(VERSION 3.25)
project(cargame)

add_executable(cargame w_demo.cpp)
target_link_libraries(cargame PRIVATE wiesel editor)

target_include_assets(cargame ${CMAKE_CURRENT_SOURCE_DIR}/assets OFF)