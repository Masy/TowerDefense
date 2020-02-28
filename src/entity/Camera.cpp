//
// Created by masy on 09.02.20.
//

#include "Camera.h"
#include "cedar/Math.h"

Camera::Camera()
{
	this->m_position = cedar::Vector3f();
	this->m_newPosition = cedar::Vector3f();
	this->m_velocity = cedar::Vector3f();
	this->m_rotateVelocity = cedar::Vector3f();
	this->m_rotation = cedar::Vector3f();
	this->m_newRotation = cedar::Vector3f();
	this->m_zoomLevel = 3;
}

void Camera::move(const float deltaX, const float deltaY, const float deltaZ)
{
	this->m_velocity.x = deltaX;
	this->m_velocity.y = deltaY;
	this->m_velocity.z = deltaZ;
}

void Camera::moveLocal(const float deltaX, const float deltaY, const float deltaZ)
{
	this->m_velocity.x = deltaX;
	this->m_velocity.y = deltaY;
	this->m_velocity.z = deltaZ;

	this->m_velocity.rotateY(-this->m_rotation.y);
}

void Camera::rotate(const float pitch, const float yaw, const float roll)
{
	this->m_rotateVelocity.x = pitch;
	this->m_rotateVelocity.y = yaw;
	this->m_rotateVelocity.z = roll;
}

void Camera::getLerpedPosition(const unsigned long currentTime, cedar::Vector3f *result) const
{
	float t = (currentTime - this->m_lastUpdate) / 50000000.0f;
	this->m_position.lerp(&this->m_newPosition, result, t);
}

void Camera::getLerpedRotation(unsigned long currentTime, cedar::Vector3f *result) const
{
	float t = (currentTime - this->m_lastUpdate) / 50000000.0f;
	this->m_rotation.lerp(&this->m_newRotation, result, t);
}

void Camera::update(const unsigned long currentTime)
{
	this->m_lastUpdate = currentTime;
	this->m_position = this->m_newPosition;
	this->m_newPosition += this->m_velocity;

	this->m_velocity *= 0.75f;

	if (this->m_velocity.x > -0.02f && this->m_velocity.x < 0.02f)
		this->m_velocity.x = 0.0f;

	if (this->m_velocity.y > -0.02f && this->m_velocity.y < 0.02f)
		this->m_velocity.y = 0.0f;

	if (this->m_velocity.z > -0.02f && this->m_velocity.z < 0.02f)
		this->m_velocity.z = 0.0f;

	this->m_rotation = this->m_newRotation;
	this->m_newRotation += this->m_rotateVelocity;
	this->m_newRotation.x = cedar::math::clamp(this->m_newRotation.x, -M_PI_2f32, M_PI_2f32);

	this->m_rotateVelocity *= 0.25f;

	if (this->m_rotateVelocity.x > -0.02f && this->m_rotateVelocity.x < 0.02f)
		this->m_rotateVelocity.x = 0.0f;

	if (this->m_rotateVelocity.y > -0.02f && this->m_rotateVelocity.y < 0.02f)
		this->m_rotateVelocity.y = 0.0f;

	if (this->m_rotateVelocity.z > -0.02f && this->m_rotateVelocity.z < 0.02f)
		this->m_rotateVelocity.z = 0.0f;
}

const cedar::Vector3f *Camera::getPosition() const
{
	return &this->m_position;
}

const cedar::Vector3f *Camera::getRotation() const
{
	return &this->m_rotation;
}

int Camera::getZoomLevel() const
{
	return this->m_zoomLevel;
}

void Camera::setZoomLevel(int newZoomLevel)
{
	this->m_zoomLevel = std::fmax(0, newZoomLevel);
}