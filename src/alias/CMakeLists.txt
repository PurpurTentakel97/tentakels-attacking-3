add_library(alias INTERFACE
            include/alias/AliasApp.hpp
            include/alias/AliasConstants.hpp
            include/alias/AliasCustomRaylib.hpp
            include/alias/AliasEvent.hpp
            include/alias/AliasHelper.hpp
            include/alias/AliasLogic.hpp
            include/alias/AliasUi.hpp
            include/alias/AliasUiLib.hpp
            include/alias/AliasUtils.hpp
)

target_include_directories(alias
                           INTERFACE include
)

target_link_libraries(alias
                      INTERFACE
                      custom_raylib
                      project_options
)