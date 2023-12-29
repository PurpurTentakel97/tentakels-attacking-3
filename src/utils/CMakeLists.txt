add_library(utils STATIC
            include/utils/Colors.hpp
            include/utils/FightResult.hpp
            include/utils/FleetResult.hpp
            Colors.cpp
            FightResult.cpp

)
target_include_directories(utils
                           PRIVATE include/utils
                           INTERFACE include
)

target_link_libraries(utils
                      PRIVATE
                      app
                      PUBLIC
                      custom_raylib
)