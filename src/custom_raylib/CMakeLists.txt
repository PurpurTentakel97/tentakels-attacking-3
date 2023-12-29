add_library(custom_raylib INTERFACE
            CustomRaylib.hpp
)

target_include_directories(custom_raylib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(custom_raylib
                      INTERFACE
                      raylib
                      alias
)
