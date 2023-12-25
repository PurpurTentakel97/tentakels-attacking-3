add_library(event INTERFACE
            include/event/EventListener.hpp
            include/event/EventManager.hpp
            include/event/GenerelEvents.hpp
            include/event/MainEvent.hpp
            include/event/UIEvents.hpp
)

target_include_directories(event INTERFACE include)
