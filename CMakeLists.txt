cmake_minimum_required(VERSION 3.14)
project(AirHockey)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++11 ")

set(SOURCE_FILES    source/main.cpp
                    source/Game.cpp
                    source/Player.cpp
                    source/Bot.cpp
                    source/exceptions.cpp
                    source/Puck.cpp
                    source/Object.cpp
                    source/math_functions.cpp
                    source/Music.cpp)

set(HEADERS includes/Game.hpp
        includes/Player.hpp
        includes/Bot.hpp
        includes/exceptions.hpp
        includes/headers.hpp
        includes/Puck.hpp
        includes/Object.hpp
        includes/math_functions.hpp
        includes/Music.hpp)

include_directories(source)
include_directories(includes)


find_library(SDL SDL2)
find_library(SDL_mixer SDL2_mixer)
find_library(SDL_ttf SDL2_ttf)
include_directories(./frameworks/SDL2.framework/Versions/A/Headers)
include_directories(./frameworks/SDL2_mixer.framework/Versions/A/Headers)
include_directories(./frameworks/SDL2_ttf.framework/Versions/A/Headers)



add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY})

# linkage
target_link_libraries(${PROJECT_NAME} ${SDL} ${SDL_mixer} ${SDL_ttf})