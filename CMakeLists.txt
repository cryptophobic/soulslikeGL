cmake_minimum_required(VERSION 3.23)
project(soulslikeGL)

set(CMAKE_CXX_STANDARD 23)

if (WIN32)
    set(OPENGL_LIBRARY
            C:/Users/dmitr/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/222.3739.54/bin/mingw/lib/)
    set(ALL_LIBS glfw3 pthread)
endif (WIN32)

if (UNIX)
    set(ALL_LIBS glfw3 GL X11 pthread Xrandr Xi dl)
endif (UNIX)

add_executable(soulslikeGL main.cpp glad.c render/gl/common/Shader.cpp render/gl/common/Shader.h images/stb_image.cpp render/gl/common/Texture.cpp render/gl/common/Texture.h objects/cube.h objects/square.h init.h render/gl/app.h render/gl/app.cpp engine/Controller.cpp engine/Controller.h settings/config.h utils/filesystem_helper.h world/Scene.cpp world/Scene.h render/gl/SceneRenderer.cpp render/gl/SceneRenderer.h world/ObjectGeometry.cpp world/ObjectGeometry.h settings/worldConfig.h utils/filesystem_helper.cpp world/Object.cpp world/Object.h world/Camera.cpp world/Camera.h world/animations/SmoothMover.cpp world/animations/SmoothMover.h world/abilities/Move.cpp world/abilities/Move.h world/abilities/FreeRotate.cpp world/abilities/FreeRotate.h world/abilities/FreeMove.cpp world/abilities/FreeMove.h world/controls/Controls.cpp world/controls/Controls.h engine/DataBus.cpp engine/DataBus.h settings/controls.h world/abilities/Ability.cpp world/abilities/Ability.h world/SceneV2.cpp world/SceneV2.h)
target_link_libraries(soulslikeGL ${ALL_LIBS})
