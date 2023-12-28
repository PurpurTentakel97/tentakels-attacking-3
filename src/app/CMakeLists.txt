add_library(app_context STATIC
            include/app/AliasApp.hpp
            include/app/AppContext.hpp
            include/app/AssetType.hpp
            include/app/AssetManager.hpp
            AppContext.cpp
            AssetManager.cpp
)

target_include_directories(app_context
                           PRIVATE include/app
                           INTERFACE include
)

target_link_libraries(app_context
                      PRIVATE
                      project_options
                      PUBLIC
                      helper
                      event
                      constants
)