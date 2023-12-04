#pragma once
#include "Ray.h"
#include "Color.h"

class Material {
public:
	virtual bool Scatter(const Ray& ray, const raycastHit_t& raycastHit, color3_t& color, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
	Lambertian(const color3_t& albedo) : m_albedo{ albedo } {}
	bool Scatter(const Ray& ray, const raycastHit_t& raycastHit, color3_t& color, Ray& scattered) const override {
		color = m_albedo;
		return true;
	}

protected:
	color3_t m_albedo;
};