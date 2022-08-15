cmake_minimum_required(VERSION 3.23)
project(soulslikeGL)

set(CMAKE_CXX_STANDARD 23)

set(ALL_LIBS glfw3 GL X11 pthread Xrandr Xi dl)


add_executable(soulslikeGL main.cpp glad.c common/Shader.cpp common/Shader.h images/stb_image.cpp common/Texture.cpp common/Texture.h objects/cube.h objects/square.h init.h render/glfw/app.h render/glfw/app.cpp engine/Controller.cpp engine/Controller.h objects/camera/Camera.cpp objects/camera/Camera.h settings/config.h utils/filesystem_helper.h world/Scene.cpp world/Scene.h render/glfw/SceneRenderer.cpp render/glfw/SceneRenderer.h world/Object.cpp world/Object.h)
target_link_libraries(soulslikeGL ${ALL_LIBS})
