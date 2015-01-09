#pragma once

#include "PhysicsComponent.h"
#include "RayCastCallback.h"

class DynamicPhysicsComponent : public PhysicsComponent
{
public:
	DynamicPhysicsComponent(GameObject::ObjectType objectType = GameObject::ObjectType::WORLD, bool fixedRotation = false, bool frictonless = false)
	{
		m_objectType = objectType;
		m_fixedRotation = fixedRotation;
		m_frictionless = frictonless;
	}
	virtual ~DynamicPhysicsComponent(){}

	inline virtual void update(World* world, GameObject* obj) override
	{
		/* Initalize the Box2D body if we haven't already. */
		if (!m_initalized && !obj->body)
		{
			m_bodyType = b2_dynamicBody;
			PhysicsComponent:init(world, obj);
		}
		/* Update the visual representation of the GameObject. */
		obj->body->SetAngularVelocity(m_angularVelocity);
		obj->position.x = obj->body->GetWorldCenter().x * PIXELS_PER_BOX2D_METER;
		obj->position.y = obj->body->GetWorldCenter().y * PIXELS_PER_BOX2D_METER;
	}
private:
};