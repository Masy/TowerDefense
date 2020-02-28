//
// Created by masy on 07.02.20.
//

#include "ToCConfig.h"

ToCConfig::ToCConfig()
{
	this->m_graphicsConfig = GraphicsConfig();
	this->m_keyConfig = KeyConfig();
	this->m_soundConfig = SoundConfig();
}

std::ostream &operator<<(std::ostream &os, ToCConfig &config)
{
	return os;
}

std::istream &operator>>(std::istream &is, ToCConfig &config)
{
	return is;
}
