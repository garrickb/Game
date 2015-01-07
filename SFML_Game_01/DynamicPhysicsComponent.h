#pragma once

#include "PhysicsComponent.h"
#include "RayCastCallback.h"

class DynamicPhysicsComponent : public PhysicsComponent
{
public:
	DynamicPhysicsComponent(bool fixedRotation = false, bool frictonless = false):m_fixedRotation(fixedRotation), m_frictionless(frictonless) {}
	virtual ~DynamicPhysicsComponent(){}

	inline virtual void update(World* world, GameObject* obj) override
	{
		/* Initalize the Box2D body if we haven't already. */
		if (!m_initalized)
			init(world, obj);

		/* Update the visual representation of the GameObject. */
		obj->body->SetAngularVelocity(m_angularVelocity);
		obj->position.x = obj->body->GetPosition().x * PIXELS_PER_BOX2D_METER;
		obj->position.y = obj->body->GetPosition().y * PIXELS_PER_BOX2D_METER;

		/* Check if we're touching the ground by raycasting downwards. */
		obj->onGround = false;

		if (obj->body && obj->body->GetContactList() && obj->body->GetContactList()->contact)
		{
			for (int i = 0; i < 5; i++)
			{
				RayCastCallback callback;
				b2Vec2 p1 = b2Vec2((obj->position.x / PIXELS_PER_BOX2D_METER) - ((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2) + i *
					((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 5), (obj->position.y / PIXELS_PER_BOX2D_METER) + (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2);

				b2Vec2 p2 = b2Vec2((obj->position.x / PIXELS_PER_BOX2D_METER) - (obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2 + i *
					(obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 5, (obj->position.y / PIXELS_PER_BOX2D_METER) + (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2 + 0.025f);

				world->box2DWorld->RayCast(&callback, p1, p2);

				if (callback.m_fixture)
				{
					obj->onGround = true;
					break;
				}
			}
		}
	}

	inline virtual void init(World* world, GameObject* obj) override
	{
		if (!m_initalized && !obj->body)
		{
			//Create Body Def and Bind to Body
			m_bodyDef = new b2BodyDef();
			m_bodyDef->type = b2_dynamicBody;
			m_bodyDef->position.x = (obj->position.x / PIXELS_PER_BOX2D_METER);
			m_bodyDef->position.y = (obj->position.y / PIXELS_PER_BOX2D_METER);
			//m_bodyDef->position.Set(obj->position.x / PIXELS_PER_BOX2D_METER, obj->position.y / PIXELS_PER_BOX2D_METER);
			obj->body = world->box2DWorld->CreateBody(m_bodyDef);
			obj->body->SetFixedRotation(m_fixedRotation);

			std::cout << "Creating Box: (" << ( obj->dimensions.x / PIXELS_PER_BOX2D_METER) << ", " << (obj->dimensions.y / PIXELS_PER_BOX2D_METER) << ")" << std::endl;

			//Create Shape
			m_shape = new b2PolygonShape();
			m_shape->SetAsBox((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f, (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2.f);

			//Create Fixture
			m_fixture = new b2FixtureDef();
			m_fixture->shape = m_shape;
			m_fixture->density = 1.f;
			m_fixture->friction = m_frictionless?0.0f:0.25f;
			m_fixture->restitution = 0.f;
			obj->body->CreateFixture(m_fixture);

			//PhysicsComponent::init(world, obj);
		}
	}
private:
	bool m_fixedRotation;
	bool m_frictionless;
};

