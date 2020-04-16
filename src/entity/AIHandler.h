//
// Created by masy on 21.03.20.
//

#ifndef TALESOFCATVENTURE_AIHANDLER_H
#define TALESOFCATVENTURE_AIHANDLER_H

#include "cedar/Vector3f.hpp"

using namespace cedar;

class AIHandler
{
private:
	unsigned int m_maxPathPointIndex;
	const Vector3f *m_pathPoints;
	float m_currentPoint;
	float m_increment;

public:
	AIHandler(unsigned int maxPathPointIndex, const Vector3f *pathPoints, float increment);

	[[nodiscard]] Vector3f getNextPosition();
	[[nodiscard]] bool reachedGoal() const;
};

#endif //TALESOFCATVENTURE_AIHANDLER_H
