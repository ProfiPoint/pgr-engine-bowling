cmake_minimum_required(VERSION 3.10)
project(pgr-sem-copakond)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp
        meshes/mesh.cpp
        meshes/mesh.h
        geometry/camera.cpp
        geometry/camera.h
        shaders/shader.cpp
        shaders/shader.h
        parser/input.h
        parser/input.cpp
        parser/objLoader.cpp
        parser/objLoader.h
        meshes/model/objMesh.cpp
        meshes/model/objMesh.h
        geometry/geometry.cpp
        geometry/geometry.h
        geometry/material.cpp
        geometry/material.h
        light/light.cpp
        light/light.h
        pgr-portable.h
        parser/mtlLoader.cpp
        parser/mtlLoader.h
        meshes/model/skybox.cpp
        meshes/model/skybox.h
        animation/spline.cpp
        animation/spline.h
        light/fog.h
        animation/catmullroll.cpp
        animation/catmullroll.h
        animation/bezier.cpp
        animation/bezier.h
        meshes/label/textLabel.cpp
        meshes/label/textLabel.h
        meshes/label/imageSequenceLabel.cpp
        meshes/label/imageSequenceLabel.h
        meshes/label/imageLabel.cpp
        meshes/label/imageLabel.h
        meshes/label/imageMoving.cpp
        meshes/label/imageMoving.h
        meshes/collision/collisionBox.cpp
        meshes/collision/collisionBox.h
        meshes/collision/rigidBody.cpp
        meshes/collision/rigidBody.h
        meshes/collision/collisionDetector.cpp
        meshes/collision/collisionDetector.h
        meshes/collision/collisionSphere.cpp
        meshes/collision/collisionSphere.h
        meshes/collision/rigidSphere.cpp
        meshes/collision/collisionShape.h
        meshes/collision/collisionShape.cpp
        scenes/Scene.h
        scenes/sampleScene.cpp
        scenes/sampleScene.h
        scenes/scene.cpp
)

if(WIN32) # WINDOWS CONFIGURATION
    add_compile_definitions(WIN32 _CONSOLE)

    target_include_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}include)
    target_link_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}lib)

    target_link_libraries(${PROJECT_NAME} PRIVATE
            debug pgrd
            optimized pgr
    )


elseif(UNIX AND NOT APPLE) # ARCH LINUX CONFIGURATION
    target_include_directories(${PROJECT_NAME} PRIVATE /usr/include)
    target_link_directories(${PROJECT_NAME} PRIVATE /usr/lib)

    target_link_libraries(${PROJECT_NAME} PRIVATE
            pgr
            assimp
            glut
            GL
            GLEW
            glfw
    )
endif()