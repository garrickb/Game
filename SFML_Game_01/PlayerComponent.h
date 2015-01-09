#pragma once

#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

#define JUMP_CASTS 10
#define GROUND_FRICTION 1.0f
#define AIR_FRICTION 1.0f
#define GROUND_SPEED 20.0f
#define AIR_SPEED 7.5f

#ifndef Components
#define Components
#include "InputComponent.h"
#include "DynamicPhysicsComponent.h"
#include "GraphicsComponent.h"
#endif

class PlayerInputComponent : public InputComponent
{
public:
	inline virtual void update(World* world, GameObject* obj) override
	{
		if (obj->body)
		{
			b2Vec2 linearVelocity = obj->body->GetLinearVelocity();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (linearVelocity.x < 0)
					obj->body->SetLinearVelocity(b2Vec2(0, linearVelocity.y));
				obj->body->ApplyForceToCenter(b2Vec2((obj->onGround ? GROUND_SPEED : AIR_SPEED) * obj->body->GetMass(), 0), true);
				//obj->body->ApplyLinearImpulse(b2Vec2((obj->onGround ? GROUND_SPEED : AIR_SPEED), 0), obj->body->GetWorldCenter(), true);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (linearVelocity.x > 0)
					obj->body->SetLinearVelocity(b2Vec2(0, linearVelocity.y));
				obj->body->ApplyForceToCenter(b2Vec2((obj->onGround ? -GROUND_SPEED : -AIR_SPEED) * obj->body->GetMass(), 0), true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (obj->onGround)
				{
					if (m_jumping)
					{
						if (m_jumpClock.getElapsedTime().asSeconds() > 0.3f)
						{
							m_jumping = false;
							m_jumpClock.restart();
						}
					}
					if (!m_jumping && m_jumpClock.getElapsedTime().asSeconds() > 0.075f)
					{
						b2Vec2 jumpImpulse(0, -obj->body->GetMass() * 12);
						m_jumping = true;

						/* Apply jump force to player. */
						obj->body->ApplyLinearImpulse(jumpImpulse, b2Vec2(obj->body->GetWorldCenter().x, obj->body->GetWorldCenter().y - (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2), true);

						m_jumpClock.restart();
						m_jumpStepClock.restart();
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				obj->body->SetLinearVelocity(b2Vec2(0, 0));
			}
		}
	}
private:
	bool m_jumping;
	sf::Clock m_jumpClock;
	sf::Clock m_jumpStepClock;
};

extern int windowHeight;
extern int windowWidth;

class PlayerPhysicsComponent : public DynamicPhysicsComponent 
{
public:
	PlayerPhysicsComponent() : DynamicPhysicsComponent(GameObject::ObjectType::PLAYER, true, true) {}
	inline virtual void update(World* world, GameObject* obj)
	{
		if (m_initalized)
		{
			obj->body->GetFixtureList()->SetFriction(((obj->onGround) ? GROUND_FRICTION : AIR_FRICTION));

			//TODO: Fix Friction Assertions

			if (obj->getShapeType() == GameObject::ShapeType::CAPSULE)
			{
				obj->body->GetFixtureList()->GetNext()->SetFriction(((obj->onGround) ? GROUND_FRICTION : AIR_FRICTION));

				obj->body->GetFixtureList()->GetNext()->GetNext()->SetFriction(((obj->onGround) ? GROUND_FRICTION : AIR_FRICTION));
			}
		}

		m_fixedRotation = true;

		DynamicPhysicsComponent::update(world, obj);
		
	}
};