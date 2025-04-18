cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp "src/Floor.h" "src/Floor.cpp"
"src/Tile.cpp"
"src/Room.h" "src/Room.cpp"
"src/tinyxml2.h" "src/tinyxml2.cpp"
"src/Kosela.h" "src/Kosela.cpp"
"src/Dummy.h" "src/Dummy.cpp" "src/Enemy.h" "src/Bomb.h" "src/Bomb.cpp")
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Rooms.xml
    ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Kosela.png
    ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/Dummy.png
    ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/bombaanimacja.png
    ${CMAKE_BINARY_DIR} COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/logo.png
    ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/arial.ttf
    ${CMAKE_BINARY_DIR} COPYONLY)
if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
