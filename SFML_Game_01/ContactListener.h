#pragma once

#include <Box2D/Box2D.h>
#include "GameObject.h"
#include "TriangleGameObject.h"
#include <iostream>


static int playerGroundCount;
static int playerGroundSlopeCount;
static int playerDynamicBodyCount;

class ContactListener : public b2ContactListener
{
private:
	inline void BeginContact(b2Contact* contact) override
	{
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();
		if ((fixA->IsSensor() || fixB->IsSensor()) && (fixA->IsSensor() != fixB->IsSensor()))
		{
			GameObject* sensor = static_cast<GameObject*>(fixA->IsSensor() ? fixA->GetBody()->GetUserData()
				: fixB->GetBody()->GetUserData());
			b2Fixture* sensorFixture = (fixA->IsSensor() ? fixA : fixB);
			GameObject* trigger = static_cast<GameObject*>(fixA->IsSensor() ? fixB->GetBody()->GetUserData() 
				: fixA->GetBody()->GetUserData());
			b2Fixture* triggerFixture = (fixA->IsSensor() ? fixB : fixA);

			switch (sensorFixture->GetFilterData().categoryBits)
			{
			case GameObject::PLAYER_JUMP_SENSOR:
				if (triggerFixture->GetFilterData().categoryBits == GameObject::DYNAMIC_WORLD)
				{
					++playerDynamicBodyCount;
					sensor->onDyanamicBody = true;
				}
				if (dynamic_cast<TriangleGameObject*>(trigger) != 0)
				{
					++playerGroundSlopeCount;
					sensor->onSlope = true;
				}
				++playerGroundCount;
				sensor->onGround = true;
				break;
			}
		}
	}

	inline void EndContact(b2Contact* contact) override
	{
		b2Fixture* fixA = contact->GetFixtureA();
		b2Fixture* fixB = contact->GetFixtureB();
		if ((fixA->IsSensor() || fixB->IsSensor()) && (fixA->IsSensor() != fixB->IsSensor()))
		{
			GameObject* sensor = static_cast<GameObject*>(fixA->IsSensor() ? fixA->GetBody()->GetUserData()
				: fixB->GetBody()->GetUserData());
			b2Fixture* sensorFixture = (fixA->IsSensor() ? fixA : fixB);
			GameObject* trigger = static_cast<GameObject*>(fixA->IsSensor() ? fixB->GetBody()->GetUserData()
				: fixA->GetBody()->GetUserData());
			b2Fixture* triggerFixture = (fixA->IsSensor() ? fixB : fixA);

			switch (sensorFixture->GetFilterData().categoryBits)
			{
			case GameObject::PLAYER_JUMP_SENSOR:
				if (--playerGroundCount == 0)
					sensor->onGround = false;
				if (dynamic_cast<TriangleGameObject*>(trigger) != 0)
				{
					--playerGroundSlopeCount;
					if (playerGroundSlopeCount == 0)
						sensor->onSlope = false;
				}
				if (triggerFixture->GetFilterData().categoryBits == GameObject::DYNAMIC_WORLD)
					if (--playerDynamicBodyCount == 0)
						sensor->onDyanamicBody = false;
				break;
			}
		}
	}
};