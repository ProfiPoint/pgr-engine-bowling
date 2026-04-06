cmake_minimum_required(VERSION 3.10)
project(pgr-sem-copakond)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(WIN32 _CONSOLE)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}include)
target_link_directories(${PROJECT_NAME} PRIVATE $ENV{PGR_FRAMEWORK_ROOT}lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
        debug pgrd
        optimized pgr
)