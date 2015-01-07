#pragma once

#include "GameObject.h"
#include "Component.h"

class PhysicsComponent : public Component
{
protected:
	virtual void init(World* world, GameObject* obj)
	{
		obj->body->SetAngularVelocity(m_angularVelocity);
		obj->position.x = obj->body->GetPosition().x * PIXELS_PER_BOX2D_METER;
		obj->position.y = obj->body->GetPosition().y * PIXELS_PER_BOX2D_METER;

		m_initalized = true;
	}

	bool m_initalized;

	float32 m_angularVelocity;

	b2BodyDef* m_bodyDef;
	b2PolygonShape* m_shape;
	b2FixtureDef* m_fixture;
};

