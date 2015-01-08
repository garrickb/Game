#pragma once

#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

#define JUMP_CASTS 15
#define GROUND_FRICTION 0.0f
#define AIR_FRICTION 0.995f
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
						if (m_jumpClock.getElapsedTime().asSeconds() > 0.5f)
						{
							m_jumping = false;
							m_jumpClock.restart();
						}
					}
					if (!m_jumping && m_jumpClock.getElapsedTime().asSeconds() > 0.025f)
					{
						b2Vec2 jumpImpulse(0, -obj->body->GetMass() * 12);
						b2Vec2 locationUnderPlayer(0.f, (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2.f);//middle of the foot sensor
						//std::cout << "Start Jump!" << std::endl;
						m_jumping = true;

						/* Find all bodies were's tanding on, so we can apply kick-off force equally spread out to objects under player. */
						std::vector<b2Body*> contactBodies;
						if (obj->body && obj->body->GetContactList() && obj->body->GetContactList()->contact)
						{
							for (int i = 0; i < JUMP_CASTS; i++)
							{
								RayCastCallback callback;
								b2Vec2 p1 = b2Vec2((obj->position.x) - ((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2) + i *
									((obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 5), (obj->position.y) + (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2);

								b2Vec2 p2 = b2Vec2((obj->position.x) - (obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 2 + i *
									(obj->dimensions.x / PIXELS_PER_BOX2D_METER) / 5, (obj->position.y) + (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2 + 0.025f);

								world->box2DWorld->RayCast(&callback, p1, p2);

								if (callback.m_fixture && callback.m_fixture->GetBody()->GetType() == b2_dynamicBody)
									contactBodies.push_back(callback.m_fixture->GetBody());
							}
						}

						/* Apply jump force to player. */
						obj->body->ApplyLinearImpulse(jumpImpulse, b2Vec2(obj->body->GetWorldCenter().x, obj->body->GetWorldCenter().y - (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2), true);

						/* Apply the force to bodies we were standing on. */
						for (std::vector<b2Body*>::iterator it = contactBodies.begin(); it != contactBodies.end(); ++it)
						{
							b2Vec2 force(0, (jumpImpulse.y / contactBodies.size()) * -1);
							(*it)->ApplyLinearImpulse(force,
								b2Vec2(obj->body->GetWorldCenter().x, obj->body->GetWorldCenter().y - (obj->dimensions.y / PIXELS_PER_BOX2D_METER) / 2), true);
						}

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
			obj->body->GetFixtureList()->SetFriction((obj->onGround) ? GROUND_FRICTION : AIR_FRICTION);

			//TODO: Fix Friction Assertions

			//if (obj->getShapeType() == GameObject::ShapeType::CAPSULE)
			//{
			//	obj->body->GetFixtureList()->GetNext()->SetFriction((obj->onGround) ? GROUND_FRICTION : AIR_FRICTION);

			//	obj->body->GetFixtureList()->GetNext()->GetNext()->SetFriction((obj->onGround) ? GROUND_FRICTION : AIR_FRICTION);
			//}
		}

		m_fixedRotation = true;

		DynamicPhysicsComponent::update(world, obj);
	}
};