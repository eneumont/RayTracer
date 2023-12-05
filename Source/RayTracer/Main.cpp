#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
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
	shared_ptr<Camera> camera = make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene s(20);
	s.SetCamera(camera);

	// create material
	auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

	// create objects -> add to scene
	for (int i = 0; i < 10; i++) {
		std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-5, 5), random(-5, 5), random(-5, -20) }, random(0.5, 2), material);
		s.AddObject(std::move(sphere));
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