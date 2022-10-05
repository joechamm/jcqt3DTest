cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(stb
	VERSION 2.27.0
	LANGUAGES CXX
) 

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE 
	include/
)

target_compile_features(stb INTERFACE cxx_std_20)