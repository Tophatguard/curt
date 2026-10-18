cmake_minimum_required(VERSION 4.4.3)
project(curt CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib"
    GIT_TAG        "5.0"
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SRC_FILES 
    "src/main.cpp"
    "src/include/*/*.cpp"
)

add_executable(curt ${SRC_FILES})

target_include_directories(curt PRIVATE src/include)
target_link_libraries(curt PRIVATE raylib)

install(TARGETS curt DESTINATION bin)
install(DIRECTORY images/ DESTINATION bin/images)
install(DIRECTORY songs/ DESTINATION bin/songs)
install(DIRECTORY sounds/ DESTINATION bin/sounds)
install(DIRECTORY fonts/ DESTINATION bin/fonts)

set(CPACK_PACKAGE_NAME "curt")
set(CPACK_PACKAGE_VERSION "1.0.0")
if(WIN32)
    set(CPACK_GENERATOR "ZIP")
else()
    set(CPACK_GENERATOR "TGZ")
endif()