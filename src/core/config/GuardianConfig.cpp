//
// Created by masy on 07.02.20.
//

#include "GuardianConfig.h"

GuardianConfig::GuardianConfig()
{
	this->m_graphicsConfig = GraphicsConfig();
	this->m_keyConfig = KeyConfig();
	this->m_soundConfig = SoundConfig();
}

std::ostream &operator<<(std::ostream &os, GuardianConfig &config)
{
	return os;
}

std::istream &operator>>(std::istream &is, GuardianConfig &config)
{
	return is;
}
