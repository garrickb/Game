#pragma once

#include "Sprite.h"
#include <fstream>

struct animationData
{
	float length;
	sf::Vector2i dimensions;
	std::vector<Sprite*> sprites;
};

struct animationMapItem
{
	animationData data;
	int count;
};

static std::map<std::string, animationMapItem> loadedAnimations;

class SpriteAnimation
{
public:
	sf::Vector2i dimensions;

	SpriteAnimation();
	SpriteAnimation(std::string filePath, bool repeat = true);
	~SpriteAnimation();

	virtual void update(World* world);
	virtual void render(Window* window);
	inline virtual void setPosition(sf::Vector2f position) { m_position = position; }
	inline virtual void setRotation(float rotation) { m_rotation = rotation; }
	inline virtual sf::Vector2f getOrigin() { return m_origin; }
	inline void setFrame(int frame) { m_frame = frame; }
	void load(std::string filePath, bool repeat = true);
	void remove();
private:
	virtual void load();
	sf::Vector2f m_origin;
	float m_rotation;
	sf::Clock m_clock;
	int m_frame;
	sf::Vector2f m_position;
	sf::Vector3i backgroundColor;
	float length;
	std::string m_filepath;
	bool m_repeat;
	bool loadFile();

	std::vector<Sprite*> sprites;
};

