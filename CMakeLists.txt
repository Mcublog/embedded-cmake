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

set(FREERTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/FreeRTOS")
set(PORT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/FreeRTOS/port")
set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(DEBUG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app/debug")

# Add includes dir
include_directories(
    .
    ${FREERTOS_DIR}/include
    ${PORT_DIR}/GCC/Posix
    ${PORT_DIR}/GCC/Posix/utils
    ${APP_DIR}
    ${DEBUG_DIR}
)

set(SOURCES
    main.c
    ${APP_DIR}/utils/app_utils.c
    ${DEBUG_DIR}/log_libs.c
)


# Find FreeRTOS lib
include_directories(${FREERTOS_DIR}/include)
link_directories(${FREERTOS_DIR}/lib)

# Create executable
add_executable(embedded_cmake
    ${SOURCES}
)

target_link_libraries(embedded_cmake freertos)

## Add pthread
target_link_libraries(${PROJECT_NAME} pthread)

set_property(TARGET embedded_cmake PROPERTY CXX_STANDARD 20)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
