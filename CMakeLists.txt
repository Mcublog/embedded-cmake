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
set(APP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(DEBUG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/app/debug")
set(BUTTON_DIR "${APP_DIR}/button")
set(IOMOCK_DIR "${APP_DIR}/io_mock")
set(MOCKS_DIR "${APP_DIR}/mocks")
set(UTILS_DIR "${APP_DIR}/utils")
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")

# Add includes dir
include_directories(
    .
    ${FREERTOS_DIR}/include
    ${APP_DIR}
    ${DEBUG_DIR}
    ${UTILS_DIR}
    ${IOMOCK_DIR}
)

# Added app files
FILE(GLOB APP_SOURCES ${APP_DIR}/*.c)

# Added io_mock
FILE(GLOB IOMOCK_SOURCES ${IOMOCK_DIR}/*.c)

# Added mocks
FILE(GLOB MOCKS_SOURCES ${MOCKS_DIR}/*.c)

# Added sources for SoftwareTimer lib
FILE(GLOB SOFTWARETIMER_SOURCES ${LIBS_DIR}/SoftwareTimer/*.c)

# Add all sources
set(SOURCES
    main.c
    ${APP_SOURCES}
    ${APP_DIR}/utils/app_utils.c
    ${DEBUG_DIR}/log_libs.c
    ${IOMOCK_SOURCES}
    ${MOCKS_SOURCES}
)

# Find FreeRTOS lib
include_directories(${FREERTOS_DIR}/include)
link_directories(${FREERTOS_DIR}/lib)

# Create executable
add_executable(embedded_cmake
    ${SOURCES}
)

# Add SoftwareTimer lib
add_library(stimer STATIC ${SOFTWARETIMER_SOURCES})
target_link_libraries(${PROJECT_NAME} stimer)

# Add FREERTOS
target_link_libraries(embedded_cmake freertos)

# Add pthread
target_link_libraries(${PROJECT_NAME} pthread)

set_property(TARGET embedded_cmake PROPERTY CXX_STANDARD 20)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
