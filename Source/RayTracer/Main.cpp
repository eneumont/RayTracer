#include <iostream>
#include "Renderer.h"

using namespace std;

int main(int, char**) {
	cout << "Hello World" << endl;

	Renderer r;
	r.Initialize();
	r.CreateWindow("RayTracer", 400, 400);

	bool quit = false;
	while (!quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	r.Shutdown();

	return 0;
}