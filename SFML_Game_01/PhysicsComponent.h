#pragma once

#include "Component.h"

class PhysicsComponent : public Component
{
protected:
	void init(World* world, GameObject* obj)
	{
		std::cout << "INIT " << m_bodyType  << std::endl;

			//Create Body Def and Bind to Body.
			m_bodyDef = new b2BodyDef();
			m_bodyDef->type = m_bodyType;
			m_bodyDef->position.Set(obj->position.x / PIXELS_PER_BOX2D_METER, obj->position.y / PIXELS_PER_BOX2D_METER);
			obj->body = world->box2DWorld->CreateBody(m_bodyDef);

			obj->body->SetFixedRotation(m_fixedRotation);
			
			//Create the shape.
			switch (obj->getShapeType())
			{
			case GameObject::ShapeType::RECTANGLE:
				std::cout << "Creating Rectangle: (" << (obj->dimensions.x / PIXELS_PER_BOX2D_METER) << ", " << (obj->dimensions.y / PIXELS_PER_BOX2D_METER) << ")" << std::endl;
				m_shape = new b2PolygonShape();
				((b2PolygonShape*)m_shape)->SetAsBox((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f, (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2.f);
				break;
			case GameObject::ShapeType::CIRCLE:
				std::cout << "Creating Circle: (" << (obj->dimensions.x / PIXELS_PER_BOX2D_METER) << ", " << (obj->dimensions.y / PIXELS_PER_BOX2D_METER) << ")" << std::endl;
				m_shape = new b2CircleShape();
				((b2CircleShape*)m_shape)->m_radius = (obj->dimensions.x / PIXELS_PER_BOX2D_METER / 2.f);
				break;
			case GameObject::CAPSULE:
				std::cout << "Creating Capsule: (" << (obj->dimensions.x / PIXELS_PER_BOX2D_METER) << ", " << (obj->dimensions.y / PIXELS_PER_BOX2D_METER) << ")" << std::endl;

				m_shape = new b2PolygonShape();
				((b2PolygonShape*)m_shape)->SetAsBox((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f, ((obj->dimensions.y - obj->dimensions.x) / PIXELS_PER_BOX2D_METER) / 2.f
					, b2Vec2(0, obj->dimensions.x / 4.f / PIXELS_PER_BOX2D_METER), 0);

				m_shape2 = new b2CircleShape();
				((b2CircleShape*)m_shape2)->m_radius = ((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f);
				((b2CircleShape*)m_shape2)->m_p.x = 0;
				((b2CircleShape*)m_shape2)->m_p.y = (obj->dimensions.y - obj->dimensions.x / 2.f) / PIXELS_PER_BOX2D_METER / 2.f;

				m_shape3 = new b2CircleShape();
				((b2CircleShape*)m_shape3)->m_radius = ((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f);
				((b2CircleShape*)m_shape3)->m_p.x = 0;
				((b2CircleShape*)m_shape3)->m_p.y = (-obj->dimensions.x / 2.f) / PIXELS_PER_BOX2D_METER / 2.f;

				m_groundSensor = new b2CircleShape();
				((b2CircleShape*)m_shape3)->m_radius = (((obj->dimensions.x + 1.f) / PIXELS_PER_BOX2D_METER) / 2.f);
				((b2CircleShape*)m_shape3)->m_p.x = 0;
				((b2CircleShape*)m_shape3)->m_p.y = (-obj->dimensions.x / 2.f) / PIXELS_PER_BOX2D_METER / 2.f;
				break;
			}

			/* Create Fixture(s) */
			if (obj->getShapeType() == GameObject::CAPSULE)
			{
				if (m_bodyType == b2_dynamicBody)
				{
					m_fixture = new b2FixtureDef();
					m_fixture->filter.categoryBits = m_objectType;
					m_fixture->shape = m_shape;
					m_fixture->density = 1.f;
					m_fixture->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture->restitution = 0.f;

					obj->body->CreateFixture(m_fixture);
				} else {
					obj->body->CreateFixture(m_shape, 0.f);
				}

				if (m_bodyType == b2_dynamicBody)
				{
					m_fixture2 = new b2FixtureDef();
					m_fixture2->filter.categoryBits = m_objectType;
					m_fixture2->shape = m_shape2;
					m_fixture2->density = 1.0f;
					m_fixture2->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture2->restitution = 0.f;

					obj->body->CreateFixture(m_fixture2);
				} else {
					obj->body->CreateFixture(m_shape2, 0.f);
				}

				if (m_bodyType == b2_dynamicBody)
				{
					m_fixture3 = new b2FixtureDef();
					m_fixture3->filter.categoryBits = m_objectType;
					m_fixture3->shape = m_shape3;
					m_fixture3->density = 1.0f;
					m_fixture3->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture3->restitution = 0.f;

					obj->body->CreateFixture(m_fixture3);
				} else {
					obj->body->CreateFixture(m_shape3, 0.f);
				}

				//m_groundSensorFixture = new b2FixtureDef();
				//m_groundSensorFixture->filter.categoryBits = m_objectType;
				//m_groundSensorFixture->filter.maskBits = GameObject::ObjectType::WORLD;
				//m_groundSensorFixture->shape = m_shape3;
				//m_groundSensorFixture->isSensor = true;
				//obj->body->CreateFixture(m_groundSensorFixture);
			} else {
				if (m_bodyType == b2_dynamicBody)
				{
					m_fixture = new b2FixtureDef();
					m_fixture->filter.categoryBits = m_objectType;
					m_fixture->shape = m_shape;
					m_fixture->density = 1.0f;
					m_fixture->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture->restitution = 0.f;

					obj->body->CreateFixture(m_fixture);
				} else {
					obj->body->CreateFixture(m_shape, 0.f);
				}

			}
			obj->body->SetUserData(this);

			if (m_bodyType != b2_dynamicBody)
			{
				obj->body->SetAngularVelocity(m_angularVelocity);
				obj->position.x = obj->body->GetPosition().x * PIXELS_PER_BOX2D_METER;
				obj->position.y = obj->body->GetPosition().y * PIXELS_PER_BOX2D_METER;
			}

		m_initalized = true;
	}

	bool m_initalized;

	float32 m_angularVelocity;

	b2BodyDef* m_bodyDef;
	b2BodyDef* m_bodyDef2;
	b2BodyDef* m_bodyDef3;
	b2Shape* m_shape;
	b2Shape* m_shape2;
	b2Shape* m_shape3;
	b2Shape* m_groundSensor;
	b2FixtureDef* m_fixture;
	b2FixtureDef* m_fixture2;
	b2FixtureDef* m_fixture3;
	b2FixtureDef* m_groundSensorFixture;


	bool m_fixedRotation;
	bool m_frictionless;
	GameObject::ObjectType m_objectType;
	b2BodyType m_bodyType;
};