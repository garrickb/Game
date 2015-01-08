#pragma once

#include "GameObject.h"

class CapsuleGameObject : public GameObject
{
public:
	CapsuleGameObject(int width, int height, std::vector<Component*> components);
	CapsuleGameObject(int x, int y, int width, int height, std::vector<Component*> components);
	~CapsuleGameObject();

	inline void update(World* world){ GameObject::update(world); };
	void render(Window* window) override;
private:
	void init(int width, int height, std::vector<Component*> components);
	sf::RectangleShape m_rect;
	sf::CircleShape m_circleTop;
	sf::CircleShape m_circleBottom;
};