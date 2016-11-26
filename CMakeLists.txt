cmake_minimum_required(VERSION 3.6)
project(ECE_Siam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
	cli/cli.cpp
	cli/cli.hpp
	siam/objects/elephant.cpp
	siam/inc/objects/elephant.hpp
	siam/objects/entity.cpp
	siam/inc/objects/entity.hpp
	main.cpp
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
)

add_executable(ECE_Siam ${SOURCE_FILES})