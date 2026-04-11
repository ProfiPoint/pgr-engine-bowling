cmake_minimum_required(VERSION 3.10)
project(pgr-sem-copakond)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(WIN32 _CONSOLE)

add_executable(${PROJECT_NAME} main.cpp
        meshes/mesh.cpp
        meshes/mesh.h
        geometry/camera.cpp
        geometry/camera.h
        shaders/shader.cpp
        shaders/shader.h
        utils/input.h
        utils/input.cpp
        utils/objLoader.cpp
        utils/objLoader.h
        meshes/objMesh.cpp
        meshes/objMesh.h
        geometry/geometry.cpp
        geometry/geometry.h
        geometry/material.cpp
        geometry/material.h
        geometry/light.cpp
        geometry/light.h
)

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}include)
target_link_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
        debug pgrd
        optimized pgr
)