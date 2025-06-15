cmake_minimum_required(VERSION 3.31)
project(keyrate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WIN32_EXECUTABLE ON)

# add compilers flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)
file(GLOB_RECURSE RESOURCE_FILES resource/*.rc)

add_executable(keyrate main.cpp
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${RESOURCE_FILES})
target_link_libraries(keyrate
        comctl32
        shell32
        user32
        gdi32
        advapi32 # for Reg* functions
)
target_include_directories(keyrate PRIVATE include)

