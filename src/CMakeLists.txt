file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_library(opensteamschema STATIC ${SOURCES})

target_include_directories(opensteamschema
    PUBLIC ${CMAKE_SOURCE_DIR}/include/opensteamschema
)