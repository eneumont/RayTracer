#include "Camera.h"
#include "MathUtils.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) :
	m_fov{ fov },
	m_aspectRatio{ aspectRatio }
{
	LookAt(eye, target, up);
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	m_eye = eye;

	m_forward = glm::normalize(eye - target);
	m_right = glm::normalize(cross(up, m_forward));
	m_up = cross(m_forward, m_right);

	CalculateViewPlane();
}

Ray Camera::GetRay(const glm::vec2& point) const {
	Ray ray;
	ray.origin = m_eye;
	ray.direction = glm::normalize(m_lowerLeft + (m_horizontal * point.x) + (m_vertical * point.y) - m_eye);

	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(m_fov);
	float halfHeight = tan(theta * 0.5f);
	float height = 2 * halfHeight;
	float width = height * m_aspectRatio;

	m_horizontal = m_right * width;
	m_vertical = m_up * height;
	m_lowerLeft = m_eye - (m_horizontal * 0.5f) - (m_vertical * 0.5f) - m_forward;
}