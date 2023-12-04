#include "Scene.h"
#include "Canvas.h"
#include "MathUtils.h"

void Scene::Render(Canvas& canvas) {
	for (int y = 0; y < canvas.getSize().y; y++) {
		for (int x = 0; x < canvas.getSize().x; x++) {
			glm::vec2 pixel(static_cast<float>(x), static_cast<float>(y));
				
			glm::vec2 point = pixel / canvas.getSize();
			
			point.y = 1.0f - point.y;

			Ray ray = m_camera->GetRay(point);

			raycastHit_t raycastHit;
			color3_t color = Trace(ray, 0, 100, raycastHit);

			canvas.DrawPoint(pixel, color4_t(color, 1));
		}
	}
}

color3_t Scene::Trace(const Ray& ray) {
	glm::vec3 direction = glm::normalize(ray.direction);

	float t = (direction.y + 1) * 0.5f;
	color3_t color = lerp(m_bottomColor, m_topColor, t);

	return color;
}

color3_t Scene::Trace(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
	bool rayHit = false;
	float closestDistance = maxDistance;

	// check if scene objects are hit by the ray
	for (const auto & object : m_objects) {
		// when checking objects don't include objects farther than closest hit (starts at max distance)
		if (object->Hit(ray, minDistance, closestDistance, raycastHit)) {
			rayHit = true;
			// set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;
		}
	}

	// if ray hit object, scatter (bounce) ray and check for next hit
	if (rayHit) {
		Ray scattered;
		color3_t color;

		if (raycastHit.material->Scatter(ray, raycastHit, color, scattered)) {
			return raycastHit.normal;
		} else {
			return color3_t{ 0, 0, 0 };
		}
	}

	// if ray not hit, return scene sky color
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	color3_t color = lerp(m_bottomColor, m_topColor, t);

	return color;
}