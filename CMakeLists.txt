cmake_minimum_required(VERSION 3.4)
project(AR_Chess)

# require C++17
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_PREFIX_PATH "C:\\OpenCV_3_4_14\\opencv\\build")
list(APPEND CMAKE_PREFIX_PATH "C:\\Libraries\\glew-2.1.0")
find_package(OpenCV REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

include_directories( ${GLEW_INCLUDE_DIRS} "C:\\Libraries\\glfw-3.3.4.bin.WIN64\\include" ${OpenCV_INCLUDE_DIRS})
file(GLOB AR_Chess_SOURCES ./e-learning_project/src/*.cpp ./e-learning_project/src/**/*.cpp
			     ./e-learning_project/include/*.h ./e-learning_project/include/**/*.h)

add_executable(AR_Chess ${AR_Chess_SOURCES})

IF (WIN32)
	# set stuff for windows
	if (GLEW_FOUND)
		include_directories( ${GLEW_INCLUDE_DIRS} "C:\\Libraries\\glfw-3.3.4.bin.WIN64\\include" ${OpenCV_INCLUDE_DIRS})
		target_link_libraries (AR_Chess ${GLEW_LIBRARIES} "C:\\Libraries\\glfw-3.3.4.bin.WIN64\\lib-vc2019\\glfw3.lib" ${OPENGL_LIBRARIES} ${OpenCV_LIBS})
	endif()

ELSE ()
	# set stuff for Linux
	include_directories( ${GLEW_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
	target_link_libraries(AR_Chess ${GLEW_LIBRARIES} ${OpenCV_LIBS} ${OPENGL_LIBRARIES} stdc++ pthread)

ENDIF ()