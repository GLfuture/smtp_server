cmake_minimum_required(VERSION 3.16)
project(test)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 17)
set(SRC_LISTS app.cc)
set(CMAKE_INSTALL_PREFIX ../../)
include_directories(../include)
link_directories(../lib)
add_subdirectory(Base64)
add_subdirectory(Smtp)
add_executable(test ${SRC_LISTS})
target_link_libraries(test smtp_server conn reactor)
set_target_properties(base64 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
set_target_properties(smtp_server PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../lib)
install(TARGETS test DESTINATION bin)

