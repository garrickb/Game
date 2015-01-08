#pragma once

#include "GameObject.h"

class CircleGameObject : public GameObject
{
public:
	CircleGameObject(int diameter, std::vector<Component*> components);
	CircleGameObject(int x, int y, int diameter, std::vector<Component*> components);
	~CircleGameObject();

	inline void update(World* world){ GameObject::update(world); };
	void render(Window* window) override;
private:
	void init(int diameter, std::vector<Component*> components);
	sf::CircleShape m_circle;
};