#pragma once

#include "PhysicsComponent.h"

class StaticPhysicsComponent : public PhysicsComponent
{
public:
	StaticPhysicsComponent() {}
	virtual ~StaticPhysicsComponent(){}

	inline virtual void update(World* world, GameObject* obj) override
	{
		/* Initalize the Box2D body if we haven't already. */
		if (!m_initalized)
		{
			m_bodyType = b2_staticBody;
			PhysicsComponent::init(world, obj);
		}

		/* Update the visual representation of the GameObject. */
		obj->body->SetAngularVelocity(m_angularVelocity);
		obj->position.x = obj->body->GetPosition().x * PIXELS_PER_BOX2D_METER;
		obj->position.y = obj->body->GetPosition().y * PIXELS_PER_BOX2D_METER;
	}
};
