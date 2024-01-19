add_library(utils STATIC
            include/utils/Colors.hpp
            include/utils/ResultFight.hpp
            include/utils/ResultFleet.hpp
            include/utils/ResultMerge.hpp
            include/utils/LayeredVector.hpp
            include/utils/Vec2.hpp
            include/utils/FleetInstructionType.hpp
            include/utils/Concepts.hpp
            include/utils/RepresentationTargetPoint.hpp
            include/utils/RepresentationFleet.hpp
            include/utils/SpaceObjectType.hpp
            include/utils/RepresentationSpaceObject.hpp
            include/utils/RepresentationPlanet.hpp
            include/utils/RepresentationGalaxy.hpp
            include/utils/RepresentationPlayer.hpp
            Colors.cpp
            ResultFight.cpp
            ResultMerge.cpp

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