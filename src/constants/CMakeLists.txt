add_library(constants STATIC
            include/constants/G_Config_Enum.hpp
            include/constants/G_Config_IO.hpp
            include/constants/G_Fight.hpp
            include/constants/G_Fleet.hpp
            include/constants/G_Game_Events.hpp
            include/constants/G_Global.hpp
            include/constants/G_Planet.hpp
            include/constants/G_Player.hpp
            include/constants/G_Sound.hpp
            include/constants/G_Version.hpp
            include/constants/G_Window.hpp
            include/constants/G_World.hpp
            G_Config_Enum.cpp
            G_Config_IO.cpp
            include/constants/CConstants.hpp
            include/constants/CFiles.hpp
            include/constants/CTextProcessing.hpp
            include/constants/CResolution.hpp
            CConstants.cpp
            include/constants/HelperConfigIO.hpp
            include/constants/HelperGameEvents.hpp
            include/constants/HelperWindow.hpp
            HelperWindow.cpp
            HelperGameEvents.cpp
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