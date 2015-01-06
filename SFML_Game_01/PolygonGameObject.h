#pragma once

#include "GameObject.h"

class PolygonGameObject : public GameObject
{
public:
	PolygonGameObject(int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
	PolygonGameObject(int x, int y, int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
	~PolygonGameObject();

	void update(World* world, float dTime) override;
	void render(Window* window) override;
};