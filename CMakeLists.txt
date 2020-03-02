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
		src/core/threads/EngineThread.h
		src/core/threads/EngineThread.cpp
		src/core/threads/OpenGLThread.h
		src/core/threads/OpenGLThread.cpp
		src/core/threads/InputThread.h
		src/core/threads/InputThread.cpp
		src/core/threads/WorldThread.h
		src/core/threads/WorldThread.cpp
		src/graphics/renderer/MasterRenderer.h
		src/graphics/renderer/MasterRenderer.cpp
		src/entity/Camera.h
		src/entity/Camera.cpp
		src/world/Chunk.h
		src/world/Chunk.cpp
		src/world/World.h
		src/world/World.cpp
		src/graphics/model/ChunkModel.h src/graphics/model/ChunkModel.cpp src/graphics/renderer/TerrainRenderer.h src/graphics/renderer/TerrainRenderer.cpp)

target_include_directories(TalesOfCatventure PUBLIC
		cedar/include
		src/entity
		src/core
		src/core/config
		src/core/threads
		src/core/logging
		src/graphics/model
		src/graphics/renderer
		src/world
		src/utils)

target_link_libraries(TalesOfCatventure cedar)