#pragma once

#include <queue>
#include "Window.h"
#include "PlayerComponent.h"
#include "SpriteGameObject.h"
#include "AnimatedSpriteGameObject.h"

class Game
{
public:
	Game(){}
	inline World* getWorld() { return m_world; }
	void run();
	void update();
	void render();
private:
	sf::Time m_stepTime;
	void init();
	Window m_window;
	int m_width;
	int m_height;

	std::string m_title;
	sf::Clock m_clock;
	sf::Time m_time;

	World* m_world;

	std::vector<GameObject*> objects;

#ifdef DEBUG
	/* FPS */
	sf::Font fpsFont;
	sf::Text fpsText;
	sf::Clock fpsClock;
	const float fpsSampleRate = 0.5f;
	int fpsSampleSize;
	std::queue<float> fpsQueue;
	float fps;
#endif
};

