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
	if (body)
		setFriction(friction, body);
	if (body2)
		setFriction(friction, body2);
}

void GameObject::setFriction(float32 friction, b2Body* bod)
{
	bod->GetFixtureList()->SetFriction(friction);
	if (getShapeType() == GameObject::ShapeType::CAPSULE)
	{
		b2Fixture* fixture = bod->GetFixtureList();
		while (fixture)
		{
			fixture->SetFriction(friction);
			fixture = fixture->GetNext();
		}
	}
	/* ResetF(Source: http://box2d.org/forum/viewtopic.php?f=4&t=7631) */
	for (b2ContactEdge* contactEdge = bod->GetContactList();
		contactEdge;
		contactEdge = contactEdge->next)
	{
		contactEdge->contact->ResetFriction();
	}
}

