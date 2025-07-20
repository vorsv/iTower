cmake_minimum_required(VERSION 3.28)
project(iTower LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(iTower src/main.cpp src/Button.cpp src/Power.cpp)
# include the include directore in the cmke file
target_include_directories(iTower PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1 # Use the latest stable tag
)

FetchContent_MakeAvailable(SFML)

target_link_libraries(iTower PRIVATE sfml-graphics)