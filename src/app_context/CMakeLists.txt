add_library(app_context STATIC
            include/AppContext.h
            AppContext.cpp
)

target_include_directories(app_context PUBLIC include)

target_link_libraries(app_context
                      PUBLIC
                      helper
                      event
                      constants
)