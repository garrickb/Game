#include "GameObject.h"
#include "Component.h"

void GameObject::update(World* world)
{
	for (auto &it1 : m_components)
	{
		it1->update(world, this);
	}
}