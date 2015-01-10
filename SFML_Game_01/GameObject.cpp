#include "GameObject.h"
#include "Component.h"

void GameObject::update(World* world)
{
	for (auto &it1 : m_components)
	{
		it1->update(world, this);
	}
}

void GameObject::setFriction(float32 friction)
{
		body->GetFixtureList()->SetFriction(friction);
		if (getShapeType() == GameObject::ShapeType::CAPSULE)
		{
			b2Fixture* fixture = body->GetFixtureList();
			while (fixture)
			{
				fixture->SetFriction(friction);
				fixture = fixture->GetNext();
			}
		}
		/* Reset Friction (Source: http://box2d.org/forum/viewtopic.php?f=4&t=7631) */
		for (b2ContactEdge* contactEdge = body->GetContactList();
			contactEdge;
			contactEdge = contactEdge->next)
		{
			contactEdge->contact->ResetFriction();
		}
}
