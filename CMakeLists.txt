cmake_minimum_required(VERSION 3.6)
project(ECE_Siam)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_LIBRARY_PATH "C:\\msys64\\mingw32\\lib\\")
list(APPEND CMAKE_LIBRARY_PATH "X:\\msys64\\mingw32\\lib\\")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    cli/cli.cpp
    cli/cli.hpp
    cli/menu/menu.hpp
    cli/menu/menu.cpp
    siam/objects/elephant.cpp
    siam/inc/objects/elephant.hpp
    siam/objects/entity.cpp
    siam/inc/objects/entity.hpp
    siam/matrix.cpp
    siam/inc/matrix.hpp
    siam/objects/mountain.cpp
    siam/inc/objects/mountain.hpp
    siam/object.cpp
    siam/inc/object.hpp
    siam/player.cpp
    siam/inc/player.hpp
    siam/objects/rhinoceros.cpp
    siam/inc/objects/rhinoceros.hpp
    siam/matrixs/direction.cpp
    siam/inc/matrixs/direction.hpp
    siam/inc/exceptions/exceptions.hpp
    siam/inc/objects/types/type.hpp
    siam/inc/game.hpp
    siam/game.cpp
    siam/inc/ui/gameui.hpp
    siam/ui/games/gamecliui.cpp
    siam/inc/ui/games/gamecliui.hpp
    siam/ui/audio/FMOD.cpp
    siam/inc/ui/audio/FMOD.hpp
    siam/ui/games/gameallegroui.cpp
    siam/inc/ui/games/gameallegroui.hpp
    winhack.h
    allegro/popup.cpp
    allegro/popup.hpp
)

add_executable(ECE_Siam ${SOURCE_FILES})

if(UNIX)
	target_link_libraries(ECE_Siam ncurses)
endif(UNIX)

target_link_libraries(ECE_Siam m)

find_package(FMOD REQUIRED)
include_directories(${FMOD_INCLUDE_DIRS})
target_link_libraries(ECE_Siam ${FMOD_LIBRARIES})

find_package(ALLEGRO4 REQUIRED)
include_directories(${ALLEGRO4_INCLUDE_DIRS})
target_link_libraries(ECE_Siam ${ALLEGRO4_LIBRARIES})