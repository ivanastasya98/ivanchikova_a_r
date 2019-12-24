cmake_minimum_required(VERSION 2.8)
project(VidCap )
set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
add_executable( VidCap VidCap.cpp )
target_link_libraries( VidCap ${OpenCV_LIBS} )


