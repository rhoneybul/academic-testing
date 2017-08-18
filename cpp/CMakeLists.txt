cmake_minimum_required(VERSION 3.4.0)

project(directory_test)

set ( PROJECT_LINK_LIBS libtestUtils.dylib )
link_directories( ~/cplusplus/rthutils/build )

set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(include ~/cplusplus/rthutils/include)

file(GLOB SOURCES "src/*.cpp")

add_executable(scoring ${SOURCES})
target_link_libraries(scoring ${PROJECT_LINK_LIBS})
