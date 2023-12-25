add_library(constants STATIC
            include/constants/CConstants.h
            include/constants/CFight.hpp
            include/constants/CFiles.hpp
            include/constants/CFleet.hpp
            include/constants/CGameEvents.h
            include/constants/CGlobal.hpp
            include/constants/CPlanet.hpp
            include/constants/CPlayer.hpp
            include/constants/CSound.hpp
            include/constants/CTextProcessing.hpp
            include/constants/CWindow.h
            include/constants/CWorld.hpp
            include/constants/ConfigIO.h
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
                      PUBLIC
                      helper
                      app_context
)