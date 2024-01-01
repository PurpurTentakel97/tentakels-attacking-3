add_library(event STATIC
            include/event/EventListener.hpp
            include/event/EventManager.hpp
            include/event/EventGeneral.hpp
            include/event/EventMain.hpp
            include/event/EventsUI.hpp
            EventManager.cpp
)

target_include_directories(event
                           PRIVATE include/event
                           PUBLIC include)

target_link_libraries(event
                      PUBLIC
                      alias
                      custom_raylib
                      utils
                      project_options
)
