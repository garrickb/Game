#pragma once

#include "Main.h"
#include "Window.h"
#include "World.h"

struct mapItem
{
	sf::Texture texture;
	int count;
};

static std::map<std::string, mapItem> loadedTextures;

class Sprite
{
public:
	Sprite();
	Sprite(std::string path);
	Sprite(std::string path, int startX, int startY, int width, int height);
	virtual void load(std::string path);
	void load(std::string path, int startX, int startY, int width, int height);
	virtual ~Sprite();
	inline sf::Sprite* getSprite() { return &m_sprite; }
	inline void setRotation(float rotation) { m_rotation = rotation; }
	inline void setOrigin(sf::Vector2f origin) { m_sprite.setOrigin(origin); }
	virtual void update(World* world, float dTime);
	virtual void render(Window* window);
	int velocityX = 50;
	int velocityY = 50;
	void remove();
private:
	float m_rotation;
	int m_height;
	int m_width;
	void readFile();
	std::string m_path;
	bool loadTexture();
	sf::Texture *m_texture;
	sf::Sprite m_sprite;
};

