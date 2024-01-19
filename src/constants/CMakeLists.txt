add_library(constants STATIC
            include/constants/CConfigEnum.hpp
            include/constants/CConfigIO.hpp
            include/constants/CConstants.hpp
            include/constants/CFight.hpp
            include/constants/CFiles.hpp
            include/constants/CFleet.hpp
            include/constants/CGameEventTypes.hpp
            include/constants/CGameEvents.hpp
            include/constants/CGlobal.hpp
            include/constants/CPlanet.hpp
            include/constants/CPlayer.hpp
            include/constants/CTextProcessing.hpp
            include/constants/CSound.hpp
            include/constants/CResolution.hpp
            include/constants/CWorld.hpp
            include/constants/CWindow.hpp
            CConstants.cpp
            CGameEvents.cpp
            ConfigEnum.cpp
            ConfigIO.cpp
            CWindow.cpp
)

target_include_directories(constants
                           PRIVATE include/constants
                           INTERFACE include
)

target_link_libraries(constants
                      PRIVATE
                      app
                      helper
                      nlohmann_json::nlohmann_json
                      project_options
                      PUBLIC
                      alias
                      custom_raylib
                      utils

)