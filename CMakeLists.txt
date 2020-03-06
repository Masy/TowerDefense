cmake_minimum_required(VERSION 3.10)
project(TalesOfCatventure)

add_subdirectory(cedar)

add_executable(TalesOfCatventure
		src/core/main.cpp
		src/core/ToC.h
		src/core/ToC.cpp
		src/core/config/ToCConfig.h
		src/core/config/ToCConfig.cpp
		src/core/logging/ToCLogAppender.h
		src/core/logging/ToCLogAppender.cpp
		src/graphics/renderer/TerrainRenderer.h
		src/graphics/renderer/TerrainRenderer.cpp
		src/input/KeyHandler.h
		src/input/KeyHandler.cpp)

target_include_directories(TalesOfCatventure PUBLIC
		cedar/include
		src/core
		src/core/config
		src/core/logging
		src/graphics/renderer
		src/input)

target_link_libraries(TalesOfCatventure cedar)