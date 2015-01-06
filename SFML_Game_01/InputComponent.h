#pragma once

#include "GameObject.h"

class InputComponent
{
public:
	virtual ~InputComponent() {}
	inline virtual void update(World* world, GameObject* obj)
	{
		//std::cout << "Default Input Call" << std::endl;
	}
};

