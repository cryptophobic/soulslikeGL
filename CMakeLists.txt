cmake_minimum_required(VERSION 3.23)
project(soulslikeGL)

set(CMAKE_CXX_STANDARD 23)

set(ALL_LIBS glfw3 GL X11 pthread Xrandr Xi dl)


add_executable(soulslikeGL main.cpp glad.c common/Shader.cpp common/Shader.h)
target_link_libraries(soulslikeGL ${ALL_LIBS})
