#include "CharacterCapsuleGameObject.h"

CharacterCapsuleGameObject::CharacterCapsuleGameObject(int width, int height, std::vector<Component*> components)
	: CapsuleGameObject(width, height, components) {}

CharacterCapsuleGameObject::CharacterCapsuleGameObject(int x, int y, int width, int height, std::vector<Component*> components)
	: CapsuleGameObject(x, y, width, height, components) {}

void CharacterCapsuleGameObject::update(World* world)
{
	m_animationCollection.update(world);
	GameObject::update(world);
}

void CharacterCapsuleGameObject::render(Window* window)
{
	m_animationCollection.setPosition(sf::Vector2f(position.x, position.y));
	m_animationCollection.setRotation((float)(body->GetAngle() * RAD_TO_ANG));
	m_animationCollection.render(window);
}