#pragma once

#include "GameObject.h"

class TriangleGameObject : public GameObject
{
public:
	TriangleGameObject(float slopePercent, int width, int height, std::vector<Component*> components);
	TriangleGameObject(float slopePercent, int x, int y, int width, int height, std::vector<Component*> components);
	~TriangleGameObject();

	inline void update(World* world){ GameObject::update(world); };
	void render(Window* window) override;
	inline float getSlopePercent(){ return m_slopePercent; }
	b2Vec2 verticies[3];
private:
	void init(int width, int height, std::vector<Component*> components);
	float m_slopePercent;
	sf::ConvexShape m_tri;
};

