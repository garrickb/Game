#pragma once

#include "GameObject.h"
#include "Component.h"

class InputComponent : public Component
{
public:
	inline virtual void update(World* world, GameObject* obj) = 0;
};

