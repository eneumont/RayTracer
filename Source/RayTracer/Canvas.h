#pragma once
#include "Color.h"
#include <vector>

class Canvas {
public:
	Canvas(int width, int height, const class Renderer& renderer);
	~Canvas();

	void Update();
	void Clear(const color4_t& color);
	void DrawPoint(const glm::ivec1& point, const color4_t& color);
	glm::vec2 getSize() const { return m_size; }

	friend class Renderer;
private:
	struct SDL_Texture* m_texture{ nullptr };
	std::vector<rgba_t> m_buffer;
	glm::ivec2 m_size{ 0 };
};