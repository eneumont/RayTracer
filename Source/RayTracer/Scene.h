#pragma once
#include "Color.h"
#include "Ray.h"
#include "Camera.h"
#include "Object.h"
#include <vector>
#include <memory>

class Scene {
public:
	Scene() = default;
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas);
	color3_t Trace(const Ray& ray);
	void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }
	color3_t Trace(const Ray& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit);
	void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

private:
	std::shared_ptr<Camera> m_camera;

	color3_t m_topColor{ 0 };
	color3_t m_bottomColor{ 1 };
	std::vector<std::shared_ptr<Object>> m_objects;
};