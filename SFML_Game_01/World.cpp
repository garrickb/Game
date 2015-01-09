#include "World.h"
#include <iostream>
#include "ContactListener.h"

World::World()
	: box2DWorld(new b2World(b2Vec2(0.0f, 25.f)))
{
	ContactListener *listenerInstance = new ContactListener();
	box2DWorld->SetContactListener(listenerInstance);
	std::cout << "Initalizing World With Gravity: (" << box2DWorld->GetGravity().x << ", " << box2DWorld->GetGravity().y << ")" << std::endl;
}


World::~World()
{
}
