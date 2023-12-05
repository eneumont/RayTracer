#include "Material.h"
#include "Random.h"

bool Lambertian::Scatter(const Ray& ray, const raycastHit_t& raycastHit, color3_t& color, Ray& scattered) const {
	glm::vec3 target = raycastHit.point + raycastHit.normal + randomInUnitSphere();
	glm::vec3 direction = glm::normalize(target - raycastHit.point);

	scattered = Ray{ raycastHit.point, direction };
    color = m_albedo;

    return true;
}

bool Metal::Scatter(const Ray& ray, const raycastHit_t& raycastHit, glm::vec3& color, Ray& scattered) const {
	glm::vec3 reflected = glm::normalize(ray.direction) + raycastHit.normal;

	scattered = Ray{ raycastHit.point, reflected + randomInUnitSphere() * m_fuzz };
	color = m_albedo;
	
	return glm::dot(scattered.direction, raycastHit.normal) > 0;
}