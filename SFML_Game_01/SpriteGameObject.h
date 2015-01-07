#pragma once

#include "Sprite.h"
#include "GameObject.h"

class SpriteGameObject : public GameObject
{
public:
	~SpriteGameObject();

	SpriteGameObject(std::string path, std::vector<Component*> components);

	SpriteGameObject(std::string path, int startX, int startY, int width, int height, std::vector<Component*> components);

	void render(Window* window) override;

private:
	std::string m_path;
		Sprite m_sprite;

		bool b2Initalized = false;
		void b2Init(World* world);

		b2Body* m_body;
		b2BodyDef* m_bodyDef;
		b2PolygonShape* m_shape;
		b2FixtureDef* m_fixture;
};