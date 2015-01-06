#pragma once

#include <Box2D/Box2D.h>

class World
{
public:
	b2World* box2DWorld;
	World();
	~World();
};

