#pragma once

#include "GameObject.h"

class PhysicsComponent
{
public:
	PhysicsComponent(){}
	virtual ~PhysicsComponent(){}
	inline World* getWorld(){ return m_world; }
	virtual void update(World* world, GameObject* obj) = 0;
	inline virtual bool isOnGround() { return m_onGround; }
	bool initalized;
protected:
	virtual void init(World* world, GameObject* obj) = 0;

	bool m_onGround;

	World* m_world;
	float32 m_angularVelocity;

	b2BodyDef* m_bodyDef;
	b2PolygonShape* m_shape;
	b2FixtureDef* m_fixture;
};

