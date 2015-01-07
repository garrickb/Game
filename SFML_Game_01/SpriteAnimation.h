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

	void update(World* world);
	void render(Window* window);
	void inline setPosition(sf::Vector2f position) { m_position = position; }
	inline void setRotation(float rotation) { m_rotation = rotation; }
	inline sf::Vector2f getOrigin() { return m_origin; }
	void load();
	void load(std::string filePath);
	void remove();
private:
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

