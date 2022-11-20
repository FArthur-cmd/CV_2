cmake_minimum_required(VERSION 3.14)
project(test_programm)

set(CMAKE_CXX_STANDARD 20)

file(GLOB 
    INCLUDE_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Filters/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Filters/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.c
)

file(GLOB 
    INCLUDE_HDR 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Filters/*.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Filters/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Utils/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/contrib/*.h
)

message(STATUS "SRC ${INCLUDE_SRC}")
message(STATUS "HDR ${INCLUDE_HDR}")

if (ADDRESS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    message(STATUS "Address sanitizer is enabled")
endif()

if (UNDEFINED)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
    message(STATUS "Undefined sanitizer is enabled")
endif()

if (GDB)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    message(STATUS "Debug is enabled")
endif()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(
  apply_filter
  ${INCLUDE_SRC}
  ${INCLUDE_HDR}
  programs/apply_filter.cpp
)

add_executable(
  test_filters
  ${INCLUDE_SRC}
  ${INCLUDE_HDR}
  programs/test_filters.cpp
)

add_executable(
  apply_opencv_filter
  ${INCLUDE_SRC}
  ${INCLUDE_HDR}
  ${CMAKE_CURRENT_SOURCE_DIR}/programs/apply_opencv_filters.cpp
)

# turns off asserts
if (NDEBUG)
  target_compile_definitions(apply_filter PUBLIC NDEBUG)
  target_compile_definitions(test_filters PUBLIC NDEBUG)
  target_compile_definitions(apply_opencv_filter PUBLIC NDEBUG)
endif()

target_link_libraries( test_filters ${OpenCV_LIBS} )
target_link_libraries( apply_filter ${OpenCV_LIBS} )
target_link_libraries( apply_opencv_filter ${OpenCV_LIBS} )