cmake_minimum_required (VERSION 2.6)

include_directories("inc")

set(SRCS
    src/matrixstack.cpp
    src/TH2DrawTool.cpp
    src/TH2CB.cpp
    src/TH2TAPS.cpp
    src/a2display.cpp
    src/PollingHist.cpp
    src/CanvasTool.cpp
)

get_property(allincdirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY INCLUDE_DIRECTORIES)

ROOT_GENERATE_DICTIONARY("${CMAKE_CURRENT_SOURCE_DIR}/inc/CanvasTool.h;${CMAKE_CURRENT_SOURCE_DIR}/inc/TH2CB.h;${CMAKE_CURRENT_SOURCE_DIR}/inc/TH2TAPS.h;${CMAKE_CURRENT_SOURCE_DIR}/inc/PollingHist.h;${CMAKE_CURRENT_SOURCE_DIR}/inc/a2display.h" "${CMAKE_CURRENT_SOURCE_DIR}/inc/LinkDef.h" "${CMAKE_BINARY_DIR}/Dict.cc" "${allincdirs}")

file(GLOB_RECURSE ADDITIONAL_FILES "inc/*")
set_source_files_properties(${ADDITIONAL_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

add_library(a2display SHARED  ${SRCS} ${CMAKE_BINARY_DIR}/Dict.cc ${ADDITIONAL_FILES})
target_link_libraries(a2display ${ROOT_LIBRARIES})

add_executable(a2display_example examples/a2display_example.cpp)
target_link_libraries(a2display_example a2display ${ROOT_LIBRARIES})
