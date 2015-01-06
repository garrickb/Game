#include "AnimatedSpriteGameObject.h"

AnimatedSpriteGameObject::~AnimatedSpriteGameObject()
{
	std::cout << "Deallocated AnimatedSpriteGameObject pointing to: " << m_path << std::endl;
}

AnimatedSpriteGameObject::AnimatedSpriteGameObject(std::string path, InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: m_path(path), GameObject(input, physics, graphics)
{
	std::cout << "Allocated AnimatedSpriteGameObject pointing to: " << m_path << std::endl;

	m_sprite.load(path);
	dimensions = m_sprite.dimensions;
}

void AnimatedSpriteGameObject::update(World* world, float dTime)
{
	//std::cout << "Updating." << std::endl;
	//Update Sprite
	m_sprite.update(world, dTime);

	//Do default update.
	GameObject::update(world, dTime);

}

void AnimatedSpriteGameObject::render(Window* window)
{
	//Update position of sprite according to the object data.
	m_sprite.setPosition(position);
	m_sprite.setRotation((float) (body->GetAngle() * RAD_TO_ANG));
	m_sprite.render(window);

	//Draw the origin.
	GameObject::render(window);
}