cmake_minimum_required(VERSION 3.5)
project(embedded_cmake VERSION 0.1.0)

# Added color compiler output
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

# For debug, no change detected ...
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

set(DESKTOP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/desktop)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set(FREERTOS_DIR ${LIBS_DIR}/FreeRTOS)
set(SOFTWARE_TIMER_DIR ${LIBS_DIR}/SoftwareTimer)
set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/app)
set(DEBUG_DIR ${APP_DIR}/debug)

# Add includes dir
include_directories(
    ${DESKTOP_DIR}
    ${DEBUG_DIR}
    ${FREERTOS_DIR}/include
    ${SOFTWARE_TIMER_DIR}/include
)

# Add all sources
set(SOURCES
    ${DESKTOP_DIR}/main.c
    ${APP_DIR}/utils/app_utils.c
)

# Adde
FILE(GLOB SOURCES ${SOURCES})
include_directories(app)

# Add sub directories
add_subdirectory(app)

# Find FreeRTOS lib
link_directories(${FREERTOS_DIR})
# Find SoftwareTimer lib
link_directories(${SOFTWARE_TIMER_DIR})
# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Added libs
target_link_libraries(${PROJECT_NAME} app)
target_link_libraries(${PROJECT_NAME} stimer)
target_link_libraries(${PROJECT_NAME} freertos)
target_link_libraries(${PROJECT_NAME} pthread)

set_property(TARGET embedded_cmake PROPERTY CXX_STANDARD 20)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_executable(io_mock_test ${TEST_DIR}/io_mock_test.c)
target_link_libraries(io_mock_test app)
add_test(NAME io_mock_test
         COMMAND io_mock_test)

# enable testing functionality
enable_testing()
