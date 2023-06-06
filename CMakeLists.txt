cmake_minimum_required(VERSION 3.0)

project(server_client VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER g++)

if(WIN32)
    set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc)
    set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe)
    set(BOOST_ROOT "C:\\Users\\CDaoZhen\\Downloads\\boost_1_82_0\\boost_1_82_0")
    set(OpenCV_INCLUDE_DIRS "C:\\Users\\CDaoZhen\\Documents\\opencv\\include")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -stdlib=libc++")
    set(OpenCV_INCLUDE_DIRS "/usr/local/include/opencv4")

endif()

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(src)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} src)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
