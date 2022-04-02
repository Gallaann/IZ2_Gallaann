add_library(two_points two_points.c two_points.h)

target_include_directories(two_points PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
