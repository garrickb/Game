#pragma once

#include "Sprite.h"
#include "GameObject.h"

class SpriteGameObject : public GameObject
{
public:
	~SpriteGameObject();

	SpriteGameObject(std::string path,
		InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics);

	SpriteGameObject(std::string path, int startX, int startY, int width, int height,
		InputComponent* input,
		PhysicsComponent* physics,
		GraphicsComponent* graphics);

	void update(World* world, float dTime) override;
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