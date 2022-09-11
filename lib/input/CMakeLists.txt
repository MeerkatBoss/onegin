add_library(libinput
            text_lines.cpp)

target_include_directories(libinput PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})