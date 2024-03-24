add_library(utils STATIC
            include/utils/G_Save_Enum.hpp
            include/utils/G_Save_Version.hpp
            G_Save_Enum.cpp
            include/utils/Colors.hpp
            include/utils/ResultsUpdate.hpp
            include/utils/LayeredVector.hpp
            include/utils/Vec2.hpp
            include/utils/FleetInstructionType.hpp
            include/utils/Concepts.hpp
            include/utils/SpaceObjectType.hpp
            include/utils/RepresentationSpaceObject.hpp
            include/utils/RepresentationGalaxy.hpp
            include/utils/RepresentationPlayer.hpp
            include/utils/Probability.hpp
            include/utils/GameEventTypes.hpp
            include/utils/ResultsEvents.hpp
            include/utils/Result.hpp
            include/utils/SaveState.hpp
            Colors.cpp
            SaveState.cpp

)
target_include_directories(utils
                           PRIVATE include/utils
                           INTERFACE include
)

target_link_libraries(utils
                      PRIVATE
                      app
                      project_options
                      PUBLIC
                      alias
                      custom_raylib
)