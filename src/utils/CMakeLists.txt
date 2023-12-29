add_library(utils STATIC
            include/utils/Colors.hpp
            include/utils/FightResult.hpp
            include/utils/FleetResult.hpp
            include/utils/MergeResult.hpp
            include/utils/LayeredVector.hpp
            include/utils/Vec2.hpp
            Colors.cpp
            FightResult.cpp
            MergeResult.cpp

)
target_include_directories(utils
                           PRIVATE include/utils
                           INTERFACE include
)

target_link_libraries(utils
                      PRIVATE
                      app
                      PUBLIC
                      alias
                      custom_raylib
)