add_library(app STATIC
            include/app/AliasApp.hpp
            include/app/AppContext.hpp
            include/app/AssetType.hpp
            include/app/AssetManager.hpp
            include/app/LanguageManager.hpp
            include/app/SoundManager.hpp
            include/app/SoundType.hpp
            include/app/PlayerCollection.hpp
            include/app/PlayerData.hpp
            AppContext.cpp
            AssetManager.cpp
            LanguageManager.cpp
            SoundManager.cpp
            PlayerCollection.cpp
            PlayerData.cpp
)

target_include_directories(app
                           PRIVATE include/app
                           INTERFACE include
)

target_link_libraries(app
                      PRIVATE
                      project_options
                      PUBLIC
                      helper
                      event
                      constants
                      utils
)