cmake_minimum_required(VERSION 3.23...3.28)

project(project_matrix LANGUAGES C)
include(CTest)  # defines BUILD_TESTING

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/dist")
endif()

add_subdirectory(${PROJECT_ROOT}/man/matrix)
add_subdirectory(${PROJECT_ROOT}/src/matrix)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    # I'm the top-most project
    option(MATRIX_BUILD_TESTING "Whether to build the libmatrix tests" ${BUILD_TESTING})
    if (BUILD_TESTING AND MATRIX_BUILD_TESTING)
        set(MATRIX_BUILD_TESTING, "ON")
    elseif (BUILD_TESTING AND NOT MATRIX_BUILD_TESTING)
        message(WARNING, " will use more specific MATRIX_BUILD_TESTING=\"${MATRIX_BUILD_TESTING}\" over BUILD_TESTING=\"${BUILD_TESTING}\"")
        set(MATRIX_BUILD_TESTING, "OFF")
    elseif (NOT BUILD_TESTING AND MATRIX_BUILD_TESTING)
        message(WARNING, " will use more specific MATRIX_BUILD_TESTING=\"${MATRIX_BUILD_TESTING}\" over BUILD_TESTING=\"${BUILD_TESTING}\"")
        set(MATRIX_BUILD_TESTING, "ON")
    elseif (NOT BUILD_TESTING AND NOT MATRIX_BUILD_TESTING)
        set(MATRIX_BUILD_TESTING, "OFF")
    endif()
else()
    # I'm not the top-most project, use MATRIX_BUILD_TESTING as-is
    option(MATRIX_BUILD_TESTING "Whether to build the libmatrix tests" "OFF")
endif()
if (MATRIX_BUILD_TESTING)
    add_subdirectory(${PROJECT_ROOT}/test/matrix)
endif()
