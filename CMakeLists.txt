cmake_minimum_required(VERSION 3.10)
project(TalesOfCatventure)

add_subdirectory(cedar)

add_executable(TalesOfCatventure
		src/core/main.cpp
		src/core/ToC.h
		src/core/ToC.cpp
		src/core/threads/EngineThread.h
		src/core/threads/EngineThread.cpp
		src/core/threads/OpenGLThread.h
		src/core/threads/OpenGLThread.cpp
		src/core/threads/WorldThread.h
		src/core/threads/WorldThread.cpp
		src/core/config/ToCConfig.h
		src/core/logging/ToCLogAppender.h
		src/core/logging/ToCLogAppender.cpp
		src/graphics/renderer/MasterRenderer.h
		src/graphics/renderer/MasterRenderer.cpp
		src/core/config/ToCConfig.cpp src/entity/Camera.h src/entity/Camera.cpp src/core/threads/InputThread.h src/core/threads/InputThread.cpp)

target_include_directories(TalesOfCatventure PUBLIC
		cedar/include
		src/entity
		src/core
		src/core/config
		src/core/threads
		src/core/logging
		src/graphics/window
		src/graphics/renderer
		src/utils)

target_link_libraries(TalesOfCatventure cedar)