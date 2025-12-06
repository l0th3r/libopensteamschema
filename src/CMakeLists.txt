file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_library(openitemdef STATIC ${SOURCES})

find_path(JANSSON_INCLUDE_DIR jansson.h)
find_library(JANSSON_LIBRARY jansson)

if(NOT JANSSON_INCLUDE_DIR OR NOT JANSSON_LIBRARY)
    message(FATAL_ERROR "Jansson not found. Install libjansson-dev.")
endif()

target_include_directories(openitemdef PRIVATE ${JANSSON_INCLUDE_DIR})
target_link_libraries(openitemdef PRIVATE ${JANSSON_LIBRARY})

target_include_directories(openitemdef
    PUBLIC ${CMAKE_SOURCE_DIR}/include/openitemdef
)

if(OPENITEMDEF_ENABLE_COVERAGE)
    openitemdef_enable_coverage_for(openitemdef)
endif()