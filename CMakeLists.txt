cmake_minimum_required(VERSION 3.6)
project(ECE_Siam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
		cli/cli.cpp
		cli/cli.hpp
		elephant.cpp
		elephant.h
		entity.cpp
		entity.h
		main.cpp
		matrix.cpp
		matrix.h
		mountain.cpp
		mountain.h
		object.cpp
		object.h
		player.cpp
		player.h
		rhinoceros.cpp
		rhinoceros.h inc/matrix/direction.hpp inc/exceptions/exceptions.hpp)

add_executable(ECE_Siam ${SOURCE_FILES})