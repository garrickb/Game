#pragma once

#include <Box2D/Box2D.h>
#include <iostream>

class ContactListener : public b2ContactListener
{
	inline void BeginContact(b2Contact* contact) override
	{
		std::cout << "Contact Begun!" << std::endl;
	}

	inline void EndContact(b2Contact* contact) override
	{
		std::cout << "Contact Ended!" << std::endl;
	}
};