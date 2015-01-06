#include "PolygonGameObject.h"


PolygonGameObject::PolygonGameObject(int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: GameObject(input, physics, graphics)
{
	GameObject::dimensions = sf::Vector2f((float) height, (float) width);
}

PolygonGameObject::PolygonGameObject(int x, int y, int width, int height, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: GameObject(input, physics, graphics)
{
	position = sf::Vector2f((float) x, (float) y);
	dimensions = sf::Vector2f(width, height);

}

void PolygonGameObject::update(World* world, float dTime)
{
	//rotation += 0.01;
	//Do default update.
	GameObject::update(world, dTime);

}

void PolygonGameObject::render(Window* window)
{
	sf::RectangleShape rect = sf::RectangleShape(dimensions);
	sf::Vector2f drawPosition = sf::Vector2f(position.x, position.y);
	rect.setOrigin(dimensions.x / 2, dimensions.y / 2);
	rect.setPosition(drawPosition);
	rect.setFillColor(sf::Color::Red);
	rect.setRotation(body->GetAngle());
	rect.setOutlineThickness(-5);
	rect.setOutlineColor(sf::Color(100, 0, 0));
	window->getSfWindow()->draw(rect);

	GameObject::render(window);
}

PolygonGameObject::~PolygonGameObject()
{
}
