#include "SpriteGameObject.h"
#include <SFML/OpenGL.hpp>

SpriteGameObject::~SpriteGameObject()
{
	std::cout << "Deallocated SpriteGameObject pointing to: " << m_path << std::endl;
}

SpriteGameObject::SpriteGameObject(std::string path, std::vector<Component*> components)
	: m_path(path), GameObject(components)
{
	std::cout << "Allocated SpriteGameObject pointing to: " << m_path << std::endl;

	m_sprite.load(path);
	dimensions.x = (int) m_sprite.getSprite()->getGlobalBounds().width;
	dimensions.y = (int) m_sprite.getSprite()->getGlobalBounds().height;
}

SpriteGameObject::SpriteGameObject(	std::string path, int startX, int startY, int width, int height, std::vector<Component*> components)
	: m_path(path), GameObject(components)
{
	std::cout << "Allocated SpriteGameObject pointing to: " << m_path << std::endl;

	dimensions.x = width;
	dimensions.y = height;
	m_sprite.load(path, startX, startY, width, height);
}

void SpriteGameObject::render(Window* window)
{
	//Update position of sprite according to the object data.
	m_sprite.setOrigin(sf::Vector2f(dimensions.x / 2.f, dimensions.y / 2.f));
	m_sprite.getSprite()->setPosition(sf::Vector2f(floor(position.x), floor(position.y)));
	m_sprite.render(window);
}