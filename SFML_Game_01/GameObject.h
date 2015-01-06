#pragma once

#include "Window.h"
#include "World.h"

#define PIXELS_PER_BOX2D_METER 64

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

#ifndef GameObject_h
#define GameObject_h

#define RAD_TO_ANG 57.2957795

class GameObject
{
public:
	float rotation;
	sf::Vector2f position;
	sf::Vector2f dimensions;

	GameObject(InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics)
		: m_input(input),
		m_physics(physics),
		m_graphics(graphics) {}

	virtual void update(World* world, float dTime);

	virtual void render(Window* window);

	inline void setAngularVelocity(float32 angularVelocity) { m_angularVelocity = angularVelocity; }

	b2Body* body;

	bool onGround;
private:
	float32 m_angularVelocity;

	InputComponent* m_input;
	PhysicsComponent* m_physics;
	GraphicsComponent* m_graphics;
};

#endif