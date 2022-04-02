set(LIBRARY_NAME realisation_consistent)

file(GLOB SRC realisation.c ../realisation.h)

add_library(${LIBRARY_NAME} STATIC ${SRC})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${LIBRARY_NAME} PUBLIC storage two_points -lm)
