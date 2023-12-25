cmake_minimum_required(VERSION 3.27)
project(TentakelsAttacking3)

set(CMAKE_CXX_STANDARD 23)

include(dependencies.cmake)
find_packages()

include(project_options.cmake)
add_subdirectory(src)

add_executable(TentakelsAttacking main.cpp)
target_link_libraries(TentakelsAttacking
                      PRIVATE
                      helper
                      ui
                      project_options
)