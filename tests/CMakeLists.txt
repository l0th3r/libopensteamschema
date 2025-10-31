file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

foreach(TEST_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_FILE}
        ${PROJECT_SOURCE_DIR}/third_party/unity/src/unity.c)

    target_include_directories(${TEST_NAME} PRIVATE
        ${PROJECT_SOURCE_DIR}/third_party/unity/src
        ${PROJECT_SOURCE_DIR}/include)

    target_link_libraries(${TEST_NAME} PRIVATE
        unity
        opensteamschema)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
