//
// Created by masy on 21.03.20.
//

#ifndef GUARDIAN_AIHANDLER_H
#define GUARDIAN_AIHANDLER_H

#include "cedar/Vector3f.hpp"

using namespace cedar;

/**
 * Class for handling the AI of an entity.
 */
class AIHandler
{
private:
	/**
	 * The index of the last path point.
	 */
	unsigned int m_maxPathPointIndex;
	/**
	 * A pointer to the array of path points the AI walks along.
	 */
	const Vector3f *m_pathPoints;
	/**
	 * The current path point.
	 */
	float m_currentPoint;
	/**
	 * The increment of the path point index.
	 */
	float m_increment;

public:
	/**
	 * Creates a new AI handler.
	 *
	 * @param maxPathPointIndex The index of the last path point.
	 * @param pathPoints A constant pointer to the array of path points.
	 * @param increment The increment of the path point index.
	 */
	AIHandler(unsigned int maxPathPointIndex, const Vector3f *pathPoints, float increment);

	/**
	 * Gets the next position.
	 *
	 * @return The next position.
	 */
	[[nodiscard]] Vector3f getNextPosition();

	/**
	 * Checks whether the goal is reached.
	 *
	 * @return Whether the goal is reached.
	 */
	[[nodiscard]] bool reachedGoal() const;
};

#endif //GUARDIAN_AIHANDLER_H
