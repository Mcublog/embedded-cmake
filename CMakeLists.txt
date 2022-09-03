cmake_minimum_required(VERSION 3.5)
project(embedded_cmake VERSION 0.1.0)

# For debug, no change detected ...
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

set(FREERTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/FreeRTOS")
set(PORT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/FreeRTOS/port")

# Add includes dir
include_directories(
    .
    ${FREERTOS_DIR}/include
    ${PORT_DIR}/GCC/Posix
    ${PORT_DIR}/GCC/Posix/utils
)

# Find FreeRTOS lib
include_directories(${FREERTOS_DIR}/include)
link_directories(${FREERTOS_DIR}/lib)

# Create executable
add_executable(embedded_cmake
    main.c
    FreeRTOSConfig.h
)

target_link_libraries(embedded_cmake freertos)

## Add pthread
target_link_libraries(${PROJECT_NAME} pthread)

set_property(TARGET embedded_cmake PROPERTY CXX_STANDARD 20)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
