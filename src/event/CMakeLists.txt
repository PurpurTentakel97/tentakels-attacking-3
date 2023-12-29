add_library(event INTERFACE
            include/event/EventListener.hpp
            include/event/EventManager.hpp
            include/event/EventGeneral.hpp
            include/event/EventMain.hpp
            include/event/EventsUI.hpp
)

target_include_directories(event INTERFACE include)

target_link_libraries(event
                      INTERFACE
                      alias
                      custom_raylib
                      utils
)
