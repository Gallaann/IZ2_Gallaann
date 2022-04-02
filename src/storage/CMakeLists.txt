add_library(storage storage.c storage.h)

target_include_directories(storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(storage LINK_PUBLIC two_points)
