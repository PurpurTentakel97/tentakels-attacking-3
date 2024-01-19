add_library(app STATIC
            include/app/AppContext.hpp
            include/app/AssetType.hpp
            include/app/AssetManager.hpp
            include/app/LanguageManager.hpp
            include/app/PlayerCollection.hpp
            include/app/PlayerData.hpp
            include/app/SoundManager.hpp
            include/app/SoundType.hpp
            AppContext.cpp
            AssetManager.cpp
            LanguageManager.cpp
            PlayerCollection.cpp
            PlayerData.cpp
            SoundManager.cpp
)

target_include_directories(app
                           PRIVATE include/app
                           INTERFACE include
)

target_link_libraries(app
                      PRIVATE
                      project_options
                      PUBLIC
                      alias
                      constants
                      event
                      helper
                      utils
                      custom_raylib
)