#include "AnimatedSpriteGameObject.h"

AnimatedSpriteGameObject::~AnimatedSpriteGameObject()
{
	std::cout << "Deallocated AnimatedSpriteGameObject pointing to: " << m_path << std::endl;
}

AnimatedSpriteGameObject::AnimatedSpriteGameObject(std::string path, std::vector<Component*> components)
	: m_path(path), GameObject(components)
{
	std::cout << "Allocated AnimatedSpriteGameObject pointing to: " << m_path << std::endl;

	m_sprite.load(path);
	dimensions.x = m_sprite.dimensions.x;
	dimensions.y = m_sprite.dimensions.y;
}

void AnimatedSpriteGameObject::update(World* world)
{
	m_sprite.update(world);

	GameObject::update(world);
}

void AnimatedSpriteGameObject::render(Window* window)
{
	//Update position of sprite according to the object data.

	m_sprite.setPosition(position);
	m_sprite.setRotation((float)(body->GetAngle() * RAD_TO_ANG));
	m_sprite.render(window);
}