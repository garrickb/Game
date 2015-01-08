#include "BoxGameObject.h"

BoxGameObject::BoxGameObject(int width, int height, std::vector<Component*> components)
	: GameObject(components)
{
	init(width, height, components);
}

BoxGameObject::BoxGameObject(int x, int y, int width, int height, std::vector<Component*> components)
	: GameObject(components)
{
	position = sf::Vector2f((float) x, (float) y);
	init(width, height, components);
}

void BoxGameObject::init(int width, int height, std::vector<Component*> components)
{
	m_shapeType = ShapeType::RECTANGLE;
	GameObject::dimensions = sf::Vector2f(width, height);
	m_rect = sf::RectangleShape(dimensions);
	m_rect.setOrigin((dimensions.x / 2.f), (dimensions.y / 2.f));
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setOutlineThickness(-3);
	m_rect.setOutlineColor(sf::Color(100, 0, 0));
}

void BoxGameObject::render(Window* window)
{
	m_rect.setPosition(sf::Vector2f(position.x, position.y));
	m_rect.setRotation( (float) (body->GetAngle() * RAD_TO_ANG));
	window->getSfWindow()->draw(m_rect);
}