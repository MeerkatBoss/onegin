add_library(libsorting sorting.cpp)

target_include_directories(libsorting PUBLIC
                        ${CMAKE_CURRENT_SOURCE_DIR})