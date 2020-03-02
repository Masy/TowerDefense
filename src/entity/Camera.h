//
// Created by masy on 09.02.20.
//

#ifndef TALESOFCATVENTURE_CAMERA_H
#define TALESOFCATVENTURE_CAMERA_H

#include "cedar/Vector3f.h"
#include "cedar/Quaternionf.h"
#include <chrono>

/**
 * Entity class representing a camera.
 */
class Camera
{
private:
	/**
	 * The current position of the camera.
	 */
	cedar::Vector3f m_position;
	/**
	 * The position of the camera in the next tick.
	 *
	 * <p>This is used by the OpenGL thread to interpolate between the positions to give the impression of smooth movement.</p>
	 */
	cedar::Vector3f m_newPosition;
	/**
	 * The velocity of the camera.
	 */
	cedar::Vector3f m_velocity;
	/**
	 * The rotational velocity of the camera.
	 */
	cedar::Vector3f m_rotateVelocity;
	/**
	 * The rotation of the camera in the next tick in euler angles.
	 */
	cedar::Vector3f m_rotationEuler;
	/**
	 * The current rotation of the camera.
	 */
	cedar::Quaternionf m_rotation;
	/**
	 * The rotation of the camera in the next tick.
	 *
	 * <p>This is used by the OpenGL thread to interpolate between the rotations to give the impression of smooth rotation.</p>
	 */
	cedar::Quaternionf m_newRotation;
	/**
	 * The current zoom level of the camera
	 */
	float m_zoomLevel;
	/**
	 * The zoom level of the camera in the next tick.
	 *
	 * <p>This is used by the OpenGL thread to interpolate between the zoom levels to give the impression of a smooth zoom.</p>
	 */
	float m_newZoomLevel;
	/**
	 * The delta that will be applied to the new zoom level in the next tick.
	 */
	float m_zoomDelta;

	/**
	 * The timestamp of when the camera was updated the last time.
	 */
	unsigned long m_lastUpdate;

public:
	/**
	 * Creates a new camera.
	 */
	Camera();

	/**
	 * Moves the camera in the given direction.
	 *
	 * <p>The offset is not directly applied to the position but applied to the velocity, which will move the camera in that
	 * direction slowly.</p>
	 *
	 * @param deltaX The new velocity of the camera on the x axis.
	 * @param deltaY The new velocity of the camera on the y axis.
	 * @param deltaZ The new velocity of the camera on the z axis.
	 */
	void move(float deltaX, float deltaY, float deltaZ);
	/**
	 * Moves the camera in the given direction based on the camera's current rotation.
	 *
	 * <p>The offset is not directly applied to the position but applied to the velocity, which will move the camera in that
	 * direction slowly.</p>
	 *
	 * @param deltaX The new velocity of the camera on the forward axis.
	 * @param deltaY The new velocity of the camera on the y axis.
	 * @param deltaZ The new velocity of the camera on the sideways axis.
	 */
	void moveLocal(float deltaX, float deltaY, float deltaZ);
	/**
	 * Rotates the camera.
	 *
	 * <p>The angle is not directly applied to the rotation but applied to the rotational velocity, which will rotate the camera in that
	 * direction slowly.</p>
	 *
	 * @param pitch The rotation amount on the x axis in radians.
	 * @param yaw The rotation amount on the y axis in radians.
	 * @param roll The rotation amount on the z axis in radians.
	 */
	void rotate(float pitch, float yaw, float roll);
	/**
	 * Updates the camera.
	 *
	 * @param currentTime The current time of the tick in microseconds.
	 */
	void update(unsigned long currentTime);

	/**
	 * Gets the current position of the camera.
	 *
	 * @return a constant pointer to the current position of the camera.
	 */
	[[nodiscard]] const cedar::Vector3f *getPosition() const;
	/**
	 * Gets the linearly interpolated position of the camera.
	 *
	 * <p>The interpolation factor is calculated by the difference between the <code>currentTime</code> and
	 * {@link #m_lastUpdate}.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @param result A pointer to the vector where the interpolated position is stored.
	 */
	void getLerpedPosition(unsigned long currentTime, cedar::Vector3f *result) const;
	/**
	 * Gets the current rotation of the camera.
	 *
	 * @return a constant pointer to the current rotation of the camera.
	 */
	[[nodiscard]] const cedar::Vector3f *getRotationEuler() const;
	/**
	 * Gets the spherical interpolated rotation of the camera.
	 *
	 * <p>The interpolation factor is calculated by the difference between the <code>currentTime</code> and
	 * {@link #m_lastUpdate}.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @param result A pointer to the quaternion where the interpolated rotation is stored.
	 */
	void getSlerpedRotation(unsigned long currentTime, cedar::Quaternionf *result) const;
	/**
	 * Gets the zoom level of the camera.
	 *
	 * @return the zoom level of the camera.
	 */
	[[nodiscard]] int getZoomLevel() const;
	/**
	 * Gets the linearly interpolated zoom level of the camera.
	 *
	 * <p>The interpolation factor is calculated by the difference between the <code>currentTime</code> and
	 * {@link #m_lastUpdate}.</p>
	 *
	 * @param currentTime The current time in microseconds.
	 * @return the linearly interpolated zoom level.
	 */
	[[nodiscard]] float getLerpedZoomLevel(unsigned long currentTime) const;
	/**
	 * Sets the zoom level of the camera.
	 *
	 * @param newZoomLevel The new zoom level of the camera.
	 */
	void setZoomLevel(float newZoomLevel);
	/**
	 * Zooms the camera over time by the given amount.
	 *
	 * @param deltaZoom The amount that will be zoomed.
	 */
	void zoom(float deltaZoom);
};

#endif //TALESOFCATVENTURE_CAMERA_H
