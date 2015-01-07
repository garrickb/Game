#pragma once

#include "GameObject.h"

class Component
{
public:
	virtual void update(World* world, GameObject* obj) {}
};