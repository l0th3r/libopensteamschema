file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_library(openitemdef STATIC ${SOURCES})

target_include_directories(openitemdef
    PUBLIC ${CMAKE_SOURCE_DIR}/include/openitemdef
)