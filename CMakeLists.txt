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
        meshes/objMesh.cpp
        meshes/objMesh.h
        geometry/geometry.cpp
        geometry/geometry.h
        geometry/material.cpp
        geometry/material.h
        light/light.cpp
        light/light.h
        pgr-portable.h
        parser/mtlLoader.cpp
        parser/mtlLoader.h
        meshes/skybox.cpp
        meshes/skybox.h
        animation/spline.cpp
        animation/spline.h
        light/fog.h
        animation/catmullroll.cpp
        animation/catmullroll.h
        animation/bezier.cpp
        animation/bezier.h
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