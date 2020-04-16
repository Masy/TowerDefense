//
// Created by masy on 21.03.20.
//

#include <cmath>
#include <cedar/Cedar.hpp>

#include "AIHandler.h"

AIHandler::AIHandler(const unsigned int maxPathPointIndex, const Vector3f *pathPoints, const float increment)
{
	this->m_maxPathPointIndex = maxPathPointIndex;
	this->m_pathPoints = pathPoints;
	this->m_currentPoint = 0.0f;
	this->m_increment = increment;
}

Vector3f AIHandler::getNextPosition()
{
	this->m_currentPoint = std::fminf(static_cast<float>(this->m_maxPathPointIndex), this->m_currentPoint + this->m_increment);
	unsigned int a = std::floor(this->m_currentPoint);
	unsigned int b = std::min(this->m_maxPathPointIndex, a + 1);
	float t = this->m_currentPoint - static_cast<float>(a);
	return this->m_pathPoints[a].lerp(this->m_pathPoints[b], t);
}

bool AIHandler::reachedGoal() const {
	return static_cast<unsigned int>(this->m_currentPoint) == this->m_maxPathPointIndex;
}