#pragma once

#include "GameObject.h"

class BoxGameObject : public GameObject
{
public:
	BoxGameObject(int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
	BoxGameObject(int x, int y, int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
	~BoxGameObject();

	void update(World* world, float dTime) override;
	void render(Window* window) override;
private:

	sf::RectangleShape m_rect;
};