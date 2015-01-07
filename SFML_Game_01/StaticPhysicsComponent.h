#pragma once

#include "PhysicsComponent.h"

class StaticPhysicsComponent : public PhysicsComponent
{
public:
	StaticPhysicsComponent(bool rot = false): m_rot(rot){}
	virtual ~StaticPhysicsComponent(){}

	inline virtual void update(World* world, GameObject* obj) override
	{
		/* Initalize the Box2D body if we haven't already. */
		if (!m_initalized)
			init(world, obj);
		if (m_rot)
			m_angularVelocity = 0.5;
		/* Update the visual representation of the GameObject. */
		obj->body->SetAngularVelocity(m_angularVelocity);
		obj->position.x = obj->body->GetPosition().x * PIXELS_PER_BOX2D_METER;
		obj->position.y = obj->body->GetPosition().y * PIXELS_PER_BOX2D_METER;
	}
private:
	inline virtual void init(World* world, GameObject* obj) override
	{
		m_bodyDef = new b2BodyDef();
		m_bodyDef->type = b2_kinematicBody;
		m_bodyDef->position.Set(obj->position.x / PIXELS_PER_BOX2D_METER, obj->position.y / PIXELS_PER_BOX2D_METER);
		obj->body = world->box2DWorld->CreateBody(m_bodyDef);

		//Create Shape and Bind to Body
		m_shape = new b2PolygonShape();
		m_shape->SetAsBox((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f, (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2.f);
		obj->body->CreateFixture(m_shape, 0.f);

		PhysicsComponent::init(world, obj);
	}

	bool m_rot;

};
