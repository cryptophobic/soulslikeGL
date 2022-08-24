cmake_minimum_required(VERSION 3.23)
project(soulslikeGL)

set(CMAKE_CXX_STANDARD 23)

set(ALL_LIBS glfw3 GL X11 pthread Xrandr Xi dl)


add_executable(soulslikeGL main.cpp glad.c render/gl/common/Shader.cpp render/gl/common/Shader.h images/stb_image.cpp render/gl/common/Texture.cpp render/gl/common/Texture.h objects/cube.h objects/square.h init.h render/gl/app.h render/gl/app.cpp engine/Controller.cpp engine/Controller.h settings/config.h utils/filesystem_helper.h world/Scene.cpp world/Scene.h render/gl/SceneRenderer.cpp render/gl/SceneRenderer.h world/Object.cpp world/Object.h render/gl/common/Object.cpp render/gl/common/Object.h settings/worldConfig.h utils/filesystem_helper.cpp)
target_link_libraries(soulslikeGL ${ALL_LIBS})
