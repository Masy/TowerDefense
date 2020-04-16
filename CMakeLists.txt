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
		src/graphics/renderer/SceneRenderer.h
		src/graphics/renderer/SceneRenderer.cpp
		src/input/KeyHandler.h
		src/input/KeyHandler.cpp
		src/graphics/renderer/DebugRenderer.h
		src/graphics/renderer/DebugRenderer.cpp
		src/tdmap/TDMap.h
		src/tdmap/TDMap.cpp
		src/entity/TowerEntity.h
		src/entity/TowerEntity.cpp
		src/core/GameStates.h src/entity/EnemyEntity.h src/entity/EnemyEntity.cpp src/entity/AIHandler.h src/entity/AIHandler.cpp src/entity/Player.hpp src/entity/Player.cpp)

target_include_directories(TalesOfCatventure PUBLIC
		cedar/include
		src/core
		src/core/config
		src/core/logging
		src/graphics/renderer
		src/input
		src/tdmap
		src/entity)

target_link_libraries(TalesOfCatventure cedar)