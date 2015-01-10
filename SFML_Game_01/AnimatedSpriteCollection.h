#pragma once

#include "SpriteAnimation.h";


class AnimatedSpriteCollection
{
public:
	inline AnimatedSpriteCollection() {}
	~AnimatedSpriteCollection();
	void addAnimation(SpriteAnimation* animation);
	void addAnimation(std::string animationFilePath);
	void setActiveAnimation(int index);
	void update(World* world);
	void render(Window* window);
	inline virtual void setPosition(sf::Vector2f position) { m_position = position; }
	inline virtual void setRotation(float rotation) { m_rotation = rotation; }
private:
	std::vector<SpriteAnimation*> m_animatedSprites;
	SpriteAnimation* m_activeAnimation;
	float m_rotation;
	sf::Vector2f m_position;
};

