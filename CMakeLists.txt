cmake_minimum_required(VERSION 3.10)
project(Guardian)

add_subdirectory(cedar)

add_executable(Guardian
		src/core/main.cpp
		src/core/Guardian.h
		src/core/Guardian.cpp
		src/core/config/GuardianConfig.h
		src/core/config/GuardianConfig.cpp
		src/core/logging/GuardianLogAppender.h
		src/core/logging/GuardianLogAppender.cpp
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
		src/core/GameStates.h
		src/entity/EnemyEntity.h
		src/entity/EnemyEntity.cpp
		src/entity/AIHandler.h
		src/entity/AIHandler.cpp
		src/entity/Player.hpp
		src/entity/Player.cpp
		src/graphics/screens/IngameScreen.hpp
		src/graphics/screens/IngameScreen.cpp
		src/graphics/screens/DebugScreen.hpp
		src/graphics/screens/DebugScreen.cpp
		src/graphics/screens/EscapeScreen.hpp
		src/graphics/screens/EscapeScreen.cpp
		src/core/Towers.hpp
		src/core/Towers.cpp
		src/core/Enemies.hpp
		src/core/Enemies.cpp
		src/core/Waves.hpp
		src/core/Waves.cpp
		src/graphics/screens/GameOverScreen.hpp
		src/graphics/screens/GameOverScreen.cpp
		src/graphics/screens/WinScreen.hpp
		src/graphics/screens/WinScreen.cpp)


target_include_directories(Guardian PUBLIC
		cedar/include
		src/core
		src/core/config
		src/core/logging
		src/graphics/renderer
		src/graphics/screens
		src/input
		src/tdmap
		src/entity)

target_link_libraries(Guardian cedar)

if (UNIX)
	install(TARGETS Guardian
			COMPONENT linapp
			RUNTIME DESTINATION "/opt/Guardian"
			LIBRARY DESTINATION "/opt/Guardian"
			DESTINATION "/opt/Guardian")

	install(DIRECTORY
			DESTINATION "/opt/Guardian/logs")

	install(FILES
			resources/font/bold/lazytown_bold.ptf
			resources/font/default/lazytown.ptf
			DESTINATION "/opt/Guardian/resources/fonts")

	install(FILES
			resources/models/enemy.bmf
			resources/models/map1_noBuildZone.bmf
			resources/models/map1_path.bmf
			resources/models/map1_world.bmf
			resources/models/towerCanon_level0.bmf
			resources/models/towerCanon_level1.bmf
			resources/models/towerCanon_level2.bmf
			resources/models/towerCanon_level3.bmf
			DESTINATION "/opt/Guardian/resources/models")

	install(FILES
			resources/gui.png
			resources/icons.png
			DESTINATION "/opt/Guardian/resources/gui")

	SET(CPACK_GENERATOR "DEB")
	SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK")
elseif(WIN32)
	install(TARGETS Guardian
			COMPONENT linapp
			RUNTIME DESTINATION ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_NSIS_INSTALL_DIRECTORY}/
			LIBRARY DESTINATION ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_NSIS_INSTALL_DIRECTORY}/
			DESTINATION ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_NSIS_INSTALL_DIRECTORY})

	install(DIRECTORY
			DESTINATION ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_NSIS_INSTALL_DIRECTORY}/logs)

	install(FILES
			resources/font/bold/lazytown_bold.ptf
			resources/font/default/lazytown.ptf
			DESTINATION ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_NSIS_INSTALL_DIRECTORY}/fonts)

	install(FILES
			resources/models/enemy.bmf
			resources/models/intersection.bmf
			resources/models/map1_noBuildZone.bmf
			resources/models/map1_path.bmf
			resources/models/map1_world.bmf
			resources/models/towerCanon_level0.bmf
			resources/models/towerCanon_level1.bmf
			resources/models/towerCanon_level2.bmf
			resources/models/towerCanon_level3.bmf
			DESTINATION ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_NSIS_INSTALL_DIRECTORY}/models)

	install(FILES
			resources/gui.png
			resources/icons.png
			DESTINATION ${CPACK_NSIS_INSTALL_ROOT}/${CPACK_NSIS_INSTALL_DIRECTORY}/gui)

	SET(CPACK_GENERATOR "NSIS")
	SET(CPACK_NSIS_DISPLAY_NAME "Guardian")
	SET(CPACK_NSIS_PACKAGE_NAME "Guardian")
	SET(CPACK_NSIS_)
endif()
INCLUDE(CPack)