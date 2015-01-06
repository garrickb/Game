#include "BoxGameObject.h"


BoxGameObject::BoxGameObject(int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: GameObject(input, physics, graphics)
{
	GameObject::dimensions = sf::Vector2f((float) height, (float) width);
	m_rect = sf::RectangleShape(dimensions);
	m_rect.setOrigin((dimensions.x / 2), (dimensions.y / 2));
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setOutlineThickness(-1);
	m_rect.setOutlineColor(sf::Color(100, 0, 0));
}

BoxGameObject::BoxGameObject(int x, int y, int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: GameObject(input, physics, graphics)
{
	position = sf::Vector2f((float) x, (float) y);
	dimensions = sf::Vector2f(width, height);
	m_rect = sf::RectangleShape(dimensions);
	m_rect.setOrigin((dimensions.x / 2), (dimensions.y / 2));
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setOutlineThickness(-5);
	m_rect.setOutlineColor(sf::Color(100, 0, 0));
}

void BoxGameObject::update(World* world, float dTime)
{
	GameObject::update(world, dTime);
}

void BoxGameObject::render(Window* window)
{
	m_rect.setPosition(sf::Vector2f(position.x, position.y));
	m_rect.setRotation( (float) (body->GetAngle() * RAD_TO_ANG));
	window->getSfWindow()->draw(m_rect);

	GameObject::render(window);
}

BoxGameObject::~BoxGameObject()
{
}
