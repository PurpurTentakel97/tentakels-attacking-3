add_library(helper STATIC
            include/helper/HErrorLog.hpp
            include/helper/HFocusEvents.hpp
            include/helper/HGeneral.hpp
            include/helper/HInput.hpp
            include/helper/HPrint.hpp
            include/helper/HRandom.hpp
            include/helper/HTextProcessing.hpp
            include/helper/HVector2Operator.hpp
            include/helper/SaveLoadFile.hpp
            HErrorLog.cpp
            HFocusEvents.cpp
            HGeneral.cpp
            HInput.cpp
            HPrint.cpp
            HRandom.cpp
            HTextProcessing.cpp
            HVector2Operator.cpp
            SaveLoadFile.cpp
            include/helper/HLohmann.hpp
            include/helper/HVersion.hpp
            HVersion.cpp
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
                      ui_lib
                      project_options
                      PUBLIC
                      custom_raylib
                      alias
)