#include "CapsuleGameObject.h"
#include "RayCastCallback.h"


CapsuleGameObject::CapsuleGameObject(int width, int height, std::vector<Component*> components)
	: GameObject(components)
{
	init(width, height, components);
}

CapsuleGameObject::CapsuleGameObject(int x, int y, int width, int height, std::vector<Component*> components)
	: GameObject(components)
{
	position = sf::Vector2f((float)x, (float)y);
	init(width, height, components);
}

void CapsuleGameObject::init(int width, int height, std::vector<Component*> components)
{
	m_shapeType = ShapeType::CAPSULE;
	GameObject::dimensions = sf::Vector2f(width, height);

	m_rect = sf::RectangleShape(sf::Vector2f(width, height));
	m_rect.setOrigin(width / 2.f, height / 2.f);
	m_rect.setFillColor(sf::Color::Red);
	m_rect.setOutlineThickness(-3);
	m_rect.setOutlineColor(sf::Color(100, 0, 0));
}

void CapsuleGameObject::render(Window* window)
{
	m_rect.setPosition(sf::Vector2f(position.x, position.y));
	m_rect.setRotation((float)(body->GetAngle() * RAD_TO_ANG));

	window->getSfWindow()->draw(m_rect);

	/* Draw Origin */
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(10, 10));
	rect.setOrigin(5, 5);
	rect.setRotation(body->GetAngle()* RAD_TO_ANG);
	rect.setPosition(position);
	if (onGround)
		rect.setFillColor(sf::Color::Blue);
	else
		rect.setFillColor(sf::Color::Green);
	window->getSfWindow()->draw(rect);

}

CapsuleGameObject::~CapsuleGameObject()
{
}
