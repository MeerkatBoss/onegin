add_executable(onegin main.cpp
                text_utils.cpp
                comparators.cpp)

target_include_directories(onegin PRIVATE
                        ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(onegin libinput libsorting)