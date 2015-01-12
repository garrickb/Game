#pragma once

#include "Window.h"
#include "World.h"

#define PIXELS_PER_BOX2D_METER 64
#define OBJECT_FRICTION 0.65f

#ifndef GameObject_h
#define GameObject_h

#define RAD_TO_ANG 57.2957795

class Component;

class GameObject
{
public:
	enum ShapeType { RECTANGLE, TRIANGLE, CIRCLE, CAPSULE };

	enum ObjectType {	PLAYER = 0x0002,
						WORLD = 0x0004,
						DYNAMIC_WORLD = 0x0006,
						ENEMY = 0x0008,
						PARTICLE = 0x000A,
						PLAYER_JUMP_SENSOR = 0x000C,
						PLAYER_LEFT_SENSOR = 0x000E,
						PLAYER_RIGHT_SENSOR = 0x0011};

	sf::Vector2f position;
	sf::Vector2f dimensions;

	GameObject(std::vector<Component*> components) : m_components(components) {}

	virtual void update(World* world);

	virtual void render(Window* window) = 0;

	inline void setAngularVelocity(float32 angularVelocity) { m_angularVelocity = angularVelocity; }

	inline ShapeType getShapeType() { return m_shapeType; }

	b2Body* body;

	//Needed for unicycle on capsule game object.
	b2Body* body2;
	b2RevoluteJointDef* revoluteJointDef;
	b2RevoluteJoint* revoluteJoint;

	virtual void setFriction(float32 friction);
	virtual void setFriction(float32 friction, b2Body* bod);

	bool onGround;
	bool onSlope;

	//User for player only.
	bool onDyanamicBody = false;;
protected:
	ShapeType m_shapeType;
private:
	float32 m_angularVelocity;

	std::vector<Component*> m_components;
};

#endif