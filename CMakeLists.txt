cmake_minimum_required(VERSION 3.0)

project(server_client VERSION 0.1.0)


find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

add_subdirectory(src)
