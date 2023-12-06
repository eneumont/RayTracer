#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include <Memory>
#include <SDL.h>

using namespace std;

int main(int, char**) {
	seedRandom((uint32_t)time(nullptr));

	Renderer r;
	r.Initialize();
	r.CreateWindow("RayTracer", 400, 300);

	Canvas c(400, 300, r);

	float aspectRatio = c.getSize().x / (float)c.getSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

	Scene s(8, glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });
	s.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);
	std::shared_ptr<Material> material;

	material = std::make_shared<Lambertian>(color3_t{ 0.2f });
	auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
	s.AddObject(std::move(plane));

	// create objects -> add to scene
	/*for (int i = 0; i < 10; i++) {
		material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-5, 5), random(-5, 5), random(-5, -20) }, random(0.5, 2), material);
		s.AddObject(std::move(sphere));
	}*/

	/*auto triangle = std::make_unique<Triangle>(glm::vec3{ 5, 0, 0 }, glm::vec3{ 0, 5, 0 }, glm::vec3{ 0, 0, 5 }, material);
	s.AddObject(std::move(triangle));*/

	for (int x = -10; x < 10; x++) {
		for (int z = -10; z < 10; z++) {
			std::shared_ptr<Material> material;

			// create random material
			float r = random01();
			if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
			else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
			else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
			else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

			// set random sphere radius
			float radius = random(0.2f, 0.3f);
			// create sphere using random radius and material
			auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
			// add sphere to the scene
			s.AddObject(std::move(sphere));
		}
	}

	// render scene 
	c.Clear({ 0, 0, 0, 1 });
	s.Render(c, 50);
	c.Update();

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}

		r.PresentCanvas(c);
	}

	r.Shutdown();

	return 0;
}