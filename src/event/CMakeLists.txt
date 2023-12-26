add_library(event INTERFACE
            include/event/EventListener.hpp
            include/event/EventManager.hpp
            include/event/EventGenerel.hpp
            include/event/EventMain.hpp
            include/event/EventsUI.hpp
)

target_include_directories(event INTERFACE include)
