add_library(constants STATIC
            include/constants/CConstants.hpp
            include/constants/CFight.hpp
            include/constants/CFiles.hpp
            include/constants/CFleet.hpp
            include/constants/CGameEvents.hpp
            include/constants/CGlobal.hpp
            include/constants/CPlanet.hpp
            include/constants/CPlayer.hpp
            include/constants/CSound.hpp
            include/constants/CTextProcessing.hpp
            include/constants/CWindow.hpp
            include/constants/CWorld.hpp
            include/constants/ConfigIO.hpp
            CConstants.cpp
            CGameEvents.cpp
            CWindow.cpp
            ConfigIO.cpp
)

target_include_directories(constants
                           PRIVATE include/constants
                           INTERFACE include
)

target_link_libraries(constants
                      PRIVATE
                      project_options
                      PUBLIC
                      helper
                      app_context
)