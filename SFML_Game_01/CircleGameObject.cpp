#include "CircleGameObject.h"


CircleGameObject::CircleGameObject(int diameter, std::vector<Component*> components)
	: GameObject(components)
{
	init(diameter, components);
}

CircleGameObject::CircleGameObject(int x, int y, int diameter, std::vector<Component*> components)
	: GameObject(components)
{
	position = sf::Vector2f((float)x, (float)y);
	init(diameter, components);
}

void CircleGameObject::init(int diameter, std::vector<Component*> components)
{
	m_shapeType = ShapeType::CIRCLE;
	GameObject::dimensions = sf::Vector2f(diameter, 0);
	m_circle = sf::CircleShape(diameter / 2.f);
	m_circle.setOrigin((dimensions.x / 2.f), (dimensions.y / 2.f));
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setOutlineThickness(-3);
	m_circle.setOutlineColor(sf::Color(100, 0, 0));
}

void CircleGameObject::render(Window* window)
{
	m_circle.setPosition(sf::Vector2f(position.x, position.y - (dimensions.x/2.f)));
	m_circle.setRotation((float)(body->GetAngle() * RAD_TO_ANG));
	window->getSfWindow()->draw(m_circle);
}

CircleGameObject::~CircleGameObject()
{
}
