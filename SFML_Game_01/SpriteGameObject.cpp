#include "SpriteGameObject.h"
#include <SFML/OpenGL.hpp>

SpriteGameObject::~SpriteGameObject()
{
	std::cout << "Deallocated SpriteGameObject pointing to: " << m_path << std::endl;
}

SpriteGameObject::SpriteGameObject(std::string path, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: m_path(path), GameObject(input, physics, graphics)
{
	std::cout << "Allocated SpriteGameObject pointing to: " << m_path << std::endl;

	m_sprite.load(path);
	dimensions.x = (m_sprite.getSprite()->getGlobalBounds().width);
	dimensions.y = m_sprite.getSprite()->getGlobalBounds().height;
}

SpriteGameObject::SpriteGameObject(	std::string path, int startX, int startY, int width, int height, 
									InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: m_path(path), GameObject(input, physics, graphics)
{
	std::cout << "Allocated SpriteGameObject pointing to: " << m_path << std::endl;

	dimensions.x = (float) width;
	dimensions.y = (float) height;
	m_sprite.load(path, startX, startY, width, height);
}

void SpriteGameObject::update(World* world, float dTime)
{
	//Do default update.
	GameObject::update(world, dTime);
}

void SpriteGameObject::render(Window* window)
{
	//Update position of sprite according to the object data.
	m_sprite.setOrigin(sf::Vector2f(dimensions.x / 2, dimensions.y / 2));
	m_sprite.getSprite()->setPosition(sf::Vector2f(floor(position.x), floor(position.y)));
	m_sprite.render(window);
}