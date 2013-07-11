# this contains the common "header" for all CMakeLists.txt in the
# subdirectories!
# check for direct cmake call on this file, forbid it!
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  get_filename_component(TOP_LEVEL ${CMAKE_SOURCE_DIR}/.. REALPATH)
  message(FATAL_ERROR "\nBuild attempt in SUB-directory ${CMAKE_SOURCE_DIR} detected!\n"
    "Please create a new directory (e.g. build) in ${TOP_LEVEL} and run `cmake ..` from ${TOP_LEVEL}/build.\n"
    "Also don't forget to delete the wrongly created directory ${CMAKE_BINARY_DIR}\n\n"
    )
endif()
