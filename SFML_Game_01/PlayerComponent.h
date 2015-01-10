#pragma once

#include "GameObject.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

//TODO: Is friction broken?

#define JUMP_CASTS 10

#define GROUND_FRICTION 0.95f
#define IDLE_GROUND_FRICTION 10.f
#define DYANMIC_BODY_FRICTION 0.275f
#define AIR_FRICTION 0.0f

#define GROUND_SPEED 20.f
#define AIR_SPEED 7.5f

#ifndef Components
#define Components
#include "InputComponent.h"
#include "DynamicPhysicsComponent.h"
#include "GraphicsComponent.h"
#include "CharacterCapsuleGameObject.h"
#endif

class PlayerInputComponent : public InputComponent
{
public:
	inline virtual void update(World* world, GameObject* obj) override
	{
		//TODO: Support Different Shapes

		/* Right now we are assuming that the player is a CharacterCapsuleGameObject, we should 
		   Bring donw CharacterGameObject so it can be multiple possible shapes. */

		if (obj->body)
		{
			b2Vec2 linearVelocity = obj->body->GetLinearVelocity();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (linearVelocity.x < 0)
					obj->body->SetLinearVelocity(b2Vec2(0, linearVelocity.y));
				obj->body->ApplyForceToCenter(b2Vec2((obj->onGround ? GROUND_SPEED : AIR_SPEED) * obj->body->GetMass(), 0), true);
				//obj->body->ApplyLinearImpulse(b2Vec2((obj->onGround ? GROUND_SPEED : AIR_SPEED), 0), obj->body->GetWorldCenter(), true);
				(static_cast<CharacterCapsuleGameObject*>(obj))->keyRight = true;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (linearVelocity.x > 0)
					obj->body->SetLinearVelocity(b2Vec2(0, linearVelocity.y));
				obj->body->ApplyForceToCenter(b2Vec2((obj->onGround ? -GROUND_SPEED : -AIR_SPEED) * obj->body->GetMass(), 0), true);
				(static_cast<CharacterCapsuleGameObject*>(obj))->keyLeft = true;
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

class PlayerPhysicsComponent : public DynamicPhysicsComponent 
{
public:
	PlayerPhysicsComponent() : DynamicPhysicsComponent(GameObject::ObjectType::PLAYER, true) {}
	inline virtual void update(World* world, GameObject* obj)
	{
		if (obj->body)
		{
			CharacterCapsuleGameObject* player = (static_cast<CharacterCapsuleGameObject*>(obj));
			bool movingLeft = obj->body->GetLinearVelocity().x < -8.f / PIXELS_PER_BOX2D_METER;
			bool movingRight = obj->body->GetLinearVelocity().x > 8.f / PIXELS_PER_BOX2D_METER;
			bool notMoving = !movingLeft && !movingRight;

			if (!player->onGround)
			{
				//Air Anim
				player->setActiveAnimation(5);
			}
			else if (player->keyLeft && movingLeft)
			{
				//walk left
				player->setActiveAnimation(2);
			}
			else if (player->keyRight && movingRight)
			{
				//walk right
				player->setActiveAnimation(1);
			}
			else {
				//idle
				if (player->keyRight)
					player->setActiveAnimation(3);
				else if (player->keyLeft)
					player->setActiveAnimation(4);
				else
					player->setActiveAnimation(0);
			}


			obj->setFriction((float32)((obj->onDyanamicBody) ? DYANMIC_BODY_FRICTION : (obj->onGround) ? ((player->keyLeft || player->keyRight) ? GROUND_FRICTION : IDLE_GROUND_FRICTION) : AIR_FRICTION));

			/* Reset the key values. */
			player->keyLeft = false;
			player->keyRight = false;
		}
		DynamicPhysicsComponent::update(world, obj);
	}
};