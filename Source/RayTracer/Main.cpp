#include <iostream>
#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include <SDL.h>

using namespace std;

int main(int, char**) {
	seedRandom((uint32_t)time(nullptr));

	Renderer r;
	r.Initialize();
	r.CreateWindow("RayTracer", 400, 400);

	Canvas c(400, 400, r);

	float aspectRatio = c.getSize().x / (float)c.getSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene s;
	s.SetCamera(camera);

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

		c.Clear({ 0, 0, 0, 1});
		s.Render(c);
		c.Update();
		r.PresentCanvas(c);
	}

	r.Shutdown();

	return 0;
}