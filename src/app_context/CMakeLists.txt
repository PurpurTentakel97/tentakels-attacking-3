add_library(app_context STATIC
            include/AppContext.hpp
            AppContext.cpp
)

target_include_directories(app_context PUBLIC include)

target_link_libraries(app_context
                      PRIVATE
                      project_options
                      PUBLIC
                      helper
                      event
                      constants
)