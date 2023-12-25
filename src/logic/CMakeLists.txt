add_library(logic STATIC
            include/logic/CopyGalaxyType.hpp
            include/logic/Fleet.h
            include/logic/Galaxy.h
            include/logic/GalaxyManager.h
            include/logic/GameManager.h
            include/logic/Planet.h
            include/logic/Player.h
            include/logic/PlayerType.hpp
            include/logic/SpaceObject.h
            include/logic/TargetPoint.h
            Fleet.cpp
            Galaxy.cpp
            GalaxyManager.cpp
            GameManager.cpp
            Planet.cpp
            Player.cpp
            SpaceObject.cpp
            TargetPoint.cpp
)

target_include_directories(logic
                           PRIVATE include/logic
                           INTERFACE include
)

target_link_libraries(logic
                      PRIVATE
                      project_options
                      PUBLIC
                      helper
                      event
                      app_context
)