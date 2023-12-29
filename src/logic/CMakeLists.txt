add_library(logic STATIC
            include/logic/CopyGalaxyType.hpp
            include/logic/Fleet.hpp
            include/logic/Galaxy.hpp
            include/logic/ManagerGalaxy.hpp
            include/logic/ManagerGame.hpp
            include/logic/Planet.hpp
            include/logic/Player.hpp
            include/logic/PlayerType.hpp
            include/logic/SpaceObject.hpp
            include/logic/TargetPoint.hpp
            Fleet.cpp
            Galaxy.cpp
            ManagerGalaxy.cpp
            ManagerGame.cpp
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
                      app
                      helper
                      ui_lib
                      project_options
                      PUBLIC
                      alias
                      event
                      utils
)