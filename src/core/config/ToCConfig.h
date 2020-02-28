//
// Created by masy on 31.01.20.
//

#ifndef TALESOFCATVENTURE_TOCCONFIG_H
#define TALESOFCATVENTURE_TOCCONFIG_H

#include <iostream>
#include "cedar/Input.h"

/**
 * The configuration class storing various values.
 */
class ToCConfig
{
public:
	/**
	 * Struct storing graphic related information.
	 */
	struct GraphicsConfig
	{
		/**
		 * Whether the game should be started in fullscreen mode or not.
		 */
		bool m_fullscreen = false;
		/**
		 * The initial width of the window.
		 */
		unsigned int m_width = 1280;
		/**
		 * The initial height of the window.
		 */
		unsigned m_height = 720;
		/**
		 * The fps limit of the game.
		 */
		int m_fpsLimit = 60;
		/**
		 * The field of view of the camera in degrees.
		 */
		float m_fov = 80;
	};

	/**
	 * Struct storing key combinations.
	 */
	struct KeyConfig
	{
		/**
		 * The key combination to open the menu.
		 */
		unsigned int m_menu = {CEDAR_KEY_ESCAPE};
	};

	/**
	 * Structs storing volume information.
	 */
	struct SoundConfig
	{
		/**
		 * The overall volume of the the game.
		 */
		double m_masterVolume = 1.0f;
		/**
		 * The volume of ambient sounds.
		 */
		double m_ambientVolume = 1.0f;
		/**
		 * The volume of music.
		 */
		double m_musicVolume = 1.0f;
		/**
		 * The volume of effects.
		 */
		double m_effectsVolume = 1.0f;
	};

	/**
	 * The graphic configuration.
	 */
	GraphicsConfig m_graphicsConfig;
	/**
	 * The key configuration.
	 */
	KeyConfig m_keyConfig;
	/**
	 * The sound configuration.
	 */
	SoundConfig m_soundConfig;

	/**
	 * Creates a new configuration.
	 */
	ToCConfig();

	friend std::ostream &operator<<(std::ostream &os, ToCConfig &config);

	friend std::istream &operator>>(std::istream &is, ToCConfig &config);
};

#endif //TALESOFCATVENTURE_TOCCONFIG_H
