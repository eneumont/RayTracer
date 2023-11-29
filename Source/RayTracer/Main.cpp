#include <iostream>
#include "Renderer.h"
#include "Random.h"

using namespace std;

int main(int, char**) {
	seedRandom();

	Renderer r;
	r.Initialize();
	r.CreateWindow("RayTracer", 400, 400);

	Canvas c(400, 400, r);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

	Scene s;
	scene.SetCamera(camera);

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
	}

	r.Shutdown();

	return 0;
}