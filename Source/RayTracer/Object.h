#pragma once
#include "Material.h"
#include "Ray.h"
#include <Memory>

class Object {
public:
	Object() = default;
	Object(std::shared_ptr<Material> material) :
		m_material{ material } 
	{}

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) = 0 ;

	Material* GetMaterial() { return m_material.get(); } //might be broken

protected:
	std::shared_ptr<Material> m_material;
};