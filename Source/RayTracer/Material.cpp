#include "Material.h"
#include "Random.h"
#include "MathUtils.h"

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

bool Dielectric::Scatter(const Ray& ray, const raycastHit_t& raycastHit, glm::vec3& color, Ray& scattered) const {
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), raycastHit.normal);
    glm::vec3 refracted;

    glm::vec3 outNormal;
    float ni_over_nt;
    float cosine;

    // ray hits inside of surface ( ray -> | -> normal )
    // ray is going out of object (ray direction is facing in the same direction of the surface normal)
    if (glm::dot(ray.direction, raycastHit.normal) > 0) {
        outNormal = -raycastHit.normal;
        ni_over_nt = m_index;
        cosine = m_index * glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    } else {
        // ray hits outside of surface ( ray -> | <- normal )
        // ray is going into object (ray direction is facing in the opposite direction of the surface norma)
        outNormal = raycastHit.normal;
        ni_over_nt = 1.0f / m_index;
        cosine = -glm::dot(ray.direction, raycastHit.normal) / ray.direction.length();
    }

    // set the probability of the ray being reflected or refracted
    float reflectProbability = 1.0f;
    if (refract(ray.direction, outNormal, ni_over_nt, refracted)) {
        // use schlick and cosine (angle) to determine if ray is reflected or refracted
        reflectProbability = schlick(cosine, m_index);
    }

    // create reflected or refracted ray
    scattered = (random01() < reflectProbability) ? Ray{ raycastHit.point, reflected } : Ray{ raycastHit.point, refracted };
    color = m_albedo;

    return true;
}