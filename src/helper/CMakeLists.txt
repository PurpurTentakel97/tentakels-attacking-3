add_library(helper STATIC
            include/helper/HConcepts.hpp
            include/helper/HErrorLog.hpp
            include/helper/HFocusEvents.hpp
            include/helper/HGalaxy.hpp
            include/helper/HGeneral.hpp
            include/helper/HInput.hpp
            include/helper/HPrint.hpp
            include/helper/HRandom.hpp
            include/helper/HTextProcessing.hpp
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
                      constants
                      logic
                      ui_lib
                      PUBLIC
                      custom_raylib
                      alias
)