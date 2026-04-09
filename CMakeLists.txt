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
        renderer/shader.cpp
        renderer/shader.h
        utils/input.h
        utils/input.cpp
        geometry/objLoader.cpp
        geometry/objLoader.h
        meshes/objMesh.cpp
        meshes/objMesh.h
        geometry/geometry.cpp
        geometry/geometry.h
)

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}include)
target_link_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
        debug pgrd
        optimized pgr
)