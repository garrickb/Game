#pragma once

#include "GameObject.h"

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	inline virtual void render(GameObject* obj, Window* window) 
	{
		/* Draw Origin */
		/*
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(10, 10));
		rect.setOrigin(5, 5);
		rect.setRotation(obj->body->GetAngle()* RAD_TO_ANG);
		rect.setPosition(obj->position);
		if (obj->onGround)
			rect.setFillColor(sf::Color::Blue);
		else
			rect.setFillColor(sf::Color::Green);
		window->getSfWindow()->draw(rect);
		*/
	}
};

