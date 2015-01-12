#pragma once

#include "Component.h"
#include "TriangleGameObject.h"

/* We want our player to be heavy. */
#define PLAYER_MASS_MULTIPLYER 2.f

class PhysicsComponent : public Component
{
protected:
	void init(World* world, GameObject* obj)
	{
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
				m_shape = new b2PolygonShape();
				((b2PolygonShape*)m_shape)->SetAsBox((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f, (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2.f);
				break;
			case GameObject::ShapeType::TRIANGLE:
				m_shape = new b2PolygonShape();
				static_cast<TriangleGameObject*>(obj)->verticies[0].Set((obj->dimensions.x * static_cast<TriangleGameObject*>(obj)->getSlopePercent() - obj->dimensions.x / 2.f) / PIXELS_PER_BOX2D_METER, -obj->dimensions.y / 2.f / PIXELS_PER_BOX2D_METER);
				static_cast<TriangleGameObject*>(obj)->verticies[1].Set(obj->dimensions.x / 2.f / PIXELS_PER_BOX2D_METER, obj->dimensions.y / 2.f / PIXELS_PER_BOX2D_METER);
				static_cast<TriangleGameObject*>(obj)->verticies[2].Set(-obj->dimensions.x / 2.f / PIXELS_PER_BOX2D_METER, obj->dimensions.y / 2.f / PIXELS_PER_BOX2D_METER);

				((b2PolygonShape*)m_shape)->Set(static_cast<TriangleGameObject*>(obj)->verticies, 4);
				break;
			case GameObject::ShapeType::CIRCLE:
				m_shape = new b2CircleShape();
				((b2CircleShape*)m_shape)->m_radius = (obj->dimensions.x / PIXELS_PER_BOX2D_METER / 2.f);
				break;
			case GameObject::CAPSULE:
				m_shape = new b2PolygonShape();
				((b2PolygonShape*)m_shape)->SetAsBox(((obj->dimensions.x - 0.2f) / PIXELS_PER_BOX2D_METER) / 2.f, ((obj->dimensions.y - obj->dimensions.x) / PIXELS_PER_BOX2D_METER) / 2.f
					, b2Vec2(0, obj->dimensions.x / 4.f / PIXELS_PER_BOX2D_METER), 0);

				m_shape2 = new b2CircleShape();
				((b2CircleShape*)m_shape2)->m_radius = ((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f);
				((b2CircleShape*)m_shape2)->m_p.x = 0;
				if (m_bodyType == b2_dynamicBody)
					((b2CircleShape*)m_shape2)->m_p.y = -obj->dimensions.x  / PIXELS_PER_BOX2D_METER / 4.f;
				else
					((b2CircleShape*)m_shape2)->m_p.y = (obj->dimensions.y - obj->dimensions.x / 2.f) / PIXELS_PER_BOX2D_METER / 2.f;

				m_shape3 = new b2CircleShape();
				((b2CircleShape*)m_shape3)->m_radius = ((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2.f);
				((b2CircleShape*)m_shape3)->m_p.x = 0;
				((b2CircleShape*)m_shape3)->m_p.y = (-obj->dimensions.x / 2.f ) / PIXELS_PER_BOX2D_METER / 2.f;

				m_groundSensor = new b2PolygonShape();
				((b2PolygonShape*)m_groundSensor)->SetAsBox((obj->dimensions.x - 5.f) / PIXELS_PER_BOX2D_METER / 2.f, 5.f / PIXELS_PER_BOX2D_METER,
					b2Vec2(0, (obj->dimensions.y - obj->dimensions.x + 5.f) / PIXELS_PER_BOX2D_METER), 0);
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
					m_fixture->density = 1.f * (m_objectType == GameObject::PLAYER?PLAYER_MASS_MULTIPLYER:1);
					m_fixture->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture->restitution = 0.f;
					obj->body->CreateFixture(m_fixture);

					m_fixture2 = new b2FixtureDef();
					m_fixture2->filter.categoryBits = m_objectType;
					m_fixture2->shape = m_shape2;
					m_fixture2->density = 1.0f * (m_objectType == GameObject::PLAYER ? PLAYER_MASS_MULTIPLYER : 1);
					m_fixture2->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture2->restitution = 0.f;
					obj->body->CreateFixture(m_fixture2);

					/* Create Body Def and Bind to Body. */
					m_bodyDef2 = new b2BodyDef();
					m_bodyDef2->type = m_bodyType;
					obj->body2 = world->box2DWorld->CreateBody(m_bodyDef2);

					/* Create the _wheel_ of the unicycle */
					m_fixture3 = new b2FixtureDef();
					m_fixture3->filter.categoryBits = m_objectType;
					m_fixture3->shape = m_shape3;
					m_fixture3->density = 1.0f * (m_objectType == GameObject::PLAYER ? PLAYER_MASS_MULTIPLYER : 1);
					m_fixture3->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture3->restitution = 0.f;
					obj->body2->CreateFixture(m_fixture3);
					
					/* Bind the bodies together using a revolute joint. */
					obj->revoluteJointDef = new b2RevoluteJointDef;
					obj->revoluteJointDef->bodyA = obj->body;
					obj->revoluteJointDef->bodyB = obj->body2;
					obj->revoluteJointDef->collideConnected = false;
					obj->revoluteJointDef->localAnchorA.Set(0.f, (obj->dimensions.y - obj->dimensions.x - 5.f) / PIXELS_PER_BOX2D_METER);
					obj->revoluteJointDef->localAnchorB.Set(0.f, -obj->dimensions.x / 4.f / PIXELS_PER_BOX2D_METER);
					obj->revoluteJointDef->enableLimit = true;
					obj->revoluteJointDef->enableMotor = true;
					obj->revoluteJointDef->maxMotorTorque = 5.f;
					obj->revoluteJoint = (b2RevoluteJoint*) world->box2DWorld->CreateJoint(obj->revoluteJointDef);
				} else {
					obj->body->CreateFixture(m_shape, 0.f);
					obj->body->CreateFixture(m_shape2, 0.f);
					obj->body->CreateFixture(m_shape3, 0.f);
				}

				if (m_objectType == GameObject::PLAYER)
				{
					m_groundSensorFixture = new b2FixtureDef();
					m_groundSensorFixture->isSensor = true;
					m_groundSensorFixture->filter.categoryBits = GameObject::ObjectType::PLAYER_JUMP_SENSOR;
					m_groundSensorFixture->shape = m_groundSensor;
					obj->body->CreateFixture(m_groundSensorFixture);
				}
			} else {
				if (m_bodyType == b2_dynamicBody)
				{
					m_fixture = new b2FixtureDef();
					m_fixture->filter.categoryBits = m_objectType;
					m_fixture->shape = m_shape;
					m_fixture->density = 1.0f * (m_objectType == GameObject::PLAYER ? PLAYER_MASS_MULTIPLYER : 1);
					m_fixture->friction = m_frictionless ? 0.0f : OBJECT_FRICTION;
					m_fixture->restitution = 0.f;

					obj->body->CreateFixture(m_fixture);
				} else {
					obj->body->CreateFixture(m_shape, 0.f);
				}

			}
			if (m_bodyType != b2_dynamicBody)
			{
				obj->body->SetAngularVelocity(m_angularVelocity);
				obj->position.x = obj->body->GetPosition().x * PIXELS_PER_BOX2D_METER;
				obj->position.y = obj->body->GetPosition().y * PIXELS_PER_BOX2D_METER;
			}
			obj->body->SetUserData(obj);

		m_initalized = true;
	}

	bool m_initalized;

	float32 m_angularVelocity;

	b2BodyDef* m_bodyDef;
	b2BodyDef* m_bodyDef2;
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