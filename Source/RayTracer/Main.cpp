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

	auto material = make_shared<Lambertian>(color3_t{ 0, 0, 1 });
	
	for (int i = 0; i < 10; i++) {
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

		/*c.Clear({ 0, 0, 0, 1});
		s.Render(c);
		c.Update();*/

		//for (int i = 0; i < 1000; i++) c.DrawPoint({ random01() * c.getSize().x, random01() * c.getSize().y }, {random01(), random01(), random01(), 1});

		r.PresentCanvas(c);
	}

	r.Shutdown();

	return 0;
}