#include "Camera.h"
#include "MathUtils.h"

Camera::Camera(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up, float fov, float aspectRatio) {
	m_fov{ fov },
	m_aspectRatio{ aspectRatio }
}

void Camera::LookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) {
	m_eye = eye;
	// set the camera axis vectors (forward, right, up)
	// forward vector (eye <- target)
	m_forward = <make sure to normalize vector>
		// use cross product to create vectors
		// right = up x forward 
	m_right = <make sure to normalize vector>
		// up = forward x right
	m_up = < both vectors are normalized, no need to normalize : ) >

	CalculateViewPlane();
}

Ray Camera::GetRay(const glm::vec2& point) const {
	Ray ray;
	// the ray origin is the camera eye
	<set ray origin>
		// calculate direction from point
		ray.direction = <lower left + (horizontal * point x) + (vertical * point.y) - eye>

		return ray;
}

void Camera::CalculateViewPlane() {
	// convert fov angle (degrees) to radians
	float theta = glm::radians(m_fov);

	// calculate the width / height of the view plane
	float halfHeight = tan(theta * 0.5f);
	float height = 2 * halfHeight;
	float width = height * aspectRatio;

	// calculate horizontal vector (right vector * width)
	m_horizontal = <right * width>
		// calculate vertical vector (up vector * height)
	m_vertical = <up * height>
		// calculate lower left location (origin)
	m_lowerLeft = m_eye - (<half horizontal>) - (<half vertical>) - m_forward;
}