#include "GameObject.h"

#ifndef Components
#define Components
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#endif

#include "RayCastCallback.h"
#include "SpriteGameObject.h"

void GameObject::update(World* world, float dTime)
{
	if (m_physics->initalized)
	{
		body->SetAngularVelocity(m_angularVelocity);
		position.x = body->GetPosition().x;
		position.y = body->GetPosition().y;
		m_input->update(world, this);
	}

	m_physics->update(world, this);
	onGround = m_physics->isOnGround();
}

void GameObject::render(Window* window)
{
	m_graphics->render(this, window);

	/* Draw Raycasts */
	/*
	if (body && body->GetContactList() && body->GetContactList()->contact)
	{
		for (int i = 0; i < 6; i++)
		{
			sf::Vector2f drawPosition = sf::Vector2f(position.x - dimensions.x / 2 + i * dimensions.x / 5 - 1, position.y + dimensions.y / 2 - 5);
			sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(1, 10));
			rect.setPosition(drawPosition);

			if (onGround)
				rect.setFillColor(sf::Color::Red);
			else
				rect.setFillColor(sf::Color::White);
			window->getSfWindow()->draw(rect);
		}
	}
	*/
	
}

