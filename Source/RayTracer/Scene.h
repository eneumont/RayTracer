#pragma once
#include "Color.h"
#include "Ray.h"
#include "Camera.h"

class Scene {
public:
	Scene() = default;
	Scene(const color3_t& topColor, const color3_t& bottomColor) :
		m_topColor{ topColor },
		m_bottomColor{ bottomColor }
	{}

	void Render(class Canvas& canvas);
	color3_t Trace(const Ray& ray);

	void SetCamera(<shared pointer of Camera> camera) { m_camera = camera; }

private:
	<shared pointer of Camera> m_camera;

	color3_t m_topColor{ 0 };
	color3_t m_bottomColor{ 1 };
};