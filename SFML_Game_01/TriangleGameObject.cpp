#include "TriangleGameObject.h"
#include "DynamicPhysicsComponent.h"
#include "StaticPhysicsComponent.h"

TriangleGameObject::TriangleGameObject(float slopePercent, int width, int height, std::vector<Component*> components)
	: GameObject(components), m_slopePercent(slopePercent)
{
	init(width, height, components);
}

TriangleGameObject::TriangleGameObject(float slopePercent, int x, int y, int width, int height, std::vector<Component*> components)
	: GameObject(components), m_slopePercent(slopePercent)
{
	position = sf::Vector2f((float)x, (float)y);
	init(width, height, components);
}

void TriangleGameObject::init(int width, int height, std::vector<Component*> components)
{
	bool isStatic = true;

	/* We need to see if we're dynamic or static, because it messed up the positioning of the triangle for some reason. */
	for (auto &it1 : components)
	{
		DynamicPhysicsComponent* dynamicPhys = dynamic_cast<DynamicPhysicsComponent*>(it1);
		StaticPhysicsComponent* staticPhys = dynamic_cast<StaticPhysicsComponent*>(it1);
		if (dynamicPhys != 0)
		{
			isStatic = false;
			break;
		}
		if (staticPhys != 0)
		{
			isStatic = true;
			break;
		}
	}

	m_shapeType = ShapeType::TRIANGLE;
	m_tri = sf::ConvexShape(3);
	GameObject::dimensions = sf::Vector2f(width, height);
	if (!isStatic)
	{
		m_tri.setPoint(0, sf::Vector2f(width * m_slopePercent, -height / 6.f));
		m_tri.setPoint(1, sf::Vector2f(0, height - height / 6.f));
		m_tri.setPoint(2, sf::Vector2f(width, height - height / 6.f));
	} else {
		m_tri.setPoint(0, sf::Vector2f(width * m_slopePercent - width/ 6.f, 0));
		m_tri.setPoint(1, sf::Vector2f(-width / 6.f, height));
		m_tri.setPoint(2, sf::Vector2f(width - width / 6.f, height));
	}
	m_tri.setFillColor(sf::Color::Red);
	m_tri.setOutlineThickness(-3);

	m_tri.setOrigin(((width * m_slopePercent) + (width)) / 3.f, (((height - height / 6.f) + (height - height / 6.f) + (-height / 6.f)) / 3.f));
	m_tri.setOutlineColor(sf::Color(100, 0, 0));
}

void TriangleGameObject::render(Window* window)
{
	/* Set the position of the triangle. */
	m_tri.setPosition(sf::Vector2f(position.x, position.y));
	m_tri.setRotation((float)(body->GetAngle() * RAD_TO_ANG));
	window->getSfWindow()->draw(m_tri);
}