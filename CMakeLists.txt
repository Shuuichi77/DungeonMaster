cmake_minimum_required(VERSION 2.8)

project(dungeonMaster)

set(OpenGL_GL_PREFERENCE LEGACY)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

cmake_policy(SET CMP0012 NEW)

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(SDL_ttf REQUIRED)

set(GLEW_LIBRARY ${CMAKE_SOURCE_DIR}/third-party/libGLEW.a)

include_directories(${SDL_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR}
        ${SDL_MIXER_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIRS} glimac/include third-party/include)

set(ALL_LIBRARIES glimac ${SDLTTF_LIBRARY} ${ASSIMP_LIBRARIES} ${SDL_MIXER_LIBRARY} ${SDL_LIBRARY} ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARY})

add_subdirectory(glimac)
add_subdirectory(dungeonMaster)