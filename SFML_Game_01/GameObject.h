#pragma once

#include "Window.h"
#include "World.h"

#define PIXELS_PER_BOX2D_METER 64

#ifndef GameObject_h
#define GameObject_h

#define RAD_TO_ANG 57.2957795

class Component;

class GameObject
{
public:
	sf::Vector2f position;
	sf::Vector2f dimensions;

	GameObject(std::vector<Component*> components) : m_components(components) {}

	virtual void update(World* world);

	virtual void render(Window* window) = 0;

	inline void setAngularVelocity(float32 angularVelocity) { m_angularVelocity = angularVelocity; }

	b2Body* body;

	bool onGround;
private:
	float32 m_angularVelocity;

	std::vector<Component*> m_components;
};

#endif