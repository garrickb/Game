#pragma once

#include "GameObject.h"

class BoxGameObject : public GameObject
{
public:
	BoxGameObject(int width, int height, std::vector<Component*> components);
	BoxGameObject(int x, int y, int width, int height, std::vector<Component*> components);
	~BoxGameObject();

	inline void update(World* world){ GameObject::update(world); };
	void render(Window* window) override;
private:
	void init(int width, int height, std::vector<Component*> components);
	sf::RectangleShape m_rect;
};