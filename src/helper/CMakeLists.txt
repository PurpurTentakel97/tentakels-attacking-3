add_library(helper STATIC
            include/helper/HConcepts.hpp
            include/helper/HErrorLog.hpp
            include/helper/HFocusEvents.hpp
            include/helper/HGalaxy.hpp
            include/helper/HGameEventTypes.hpp
            include/helper/HGeneral.hpp
            include/helper/HInput.hpp
            include/helper/HLogicAlias.hpp
            include/helper/HPrint.hpp
            include/helper/HRandom.hpp
            include/helper/HResolution.hpp
            include/helper/HTextProcessing.hpp
            include/helper/HUIAlias.hpp
            include/helper/HVector2Operator.hpp
            HErrorLog.cpp
            HFocusEvents.cpp
            HGalaxy.cpp
            HGeneral.cpp
            HInput.cpp
            HPrint.cpp
            HRandom.cpp
            HTextProcessing.cpp
            HVector2Operator.cpp
)

target_include_directories(helper
                           PRIVATE include/helper
                           INTERFACE include
)

target_link_libraries(helper
                      PRIVATE
                      app
                      event
                      logic
                      nlohmann_json::nlohmann_json
                      project_options
                      PUBLIC
                      custom_raylib
                      ui_lib
)