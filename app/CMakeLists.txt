set(DEBUG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/debug")
set(IOMOCK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/io_mock")
set(UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/utils")

# Add includes dir
include_directories(
    .
    ${DEBUG_DIR}
    ${UTILS_DIR}
    ${IOMOCK_DIR}
)


file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.c)

set(SOURCES ${SOURCES})

add_library(app STATIC ${SOURCES})

