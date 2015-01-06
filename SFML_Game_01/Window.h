#pragma once

#include "Main.h"

class Window
{
public:
	Window();
	~Window();

	void create(int width, int height, const std::string title);
	void update(); 
	void display();

	inline int getWidth() const { return m_width; }
	inline int getHeight() const { return m_height; }
	inline std::string getTitle() const { return m_title; }
	inline bool isClosedRequested() const { return m_isCloseRequested; }
	inline sf::RenderWindow* getSfWindow() const { return m_window; };
private:
	bool m_isCloseRequested = false;
	int m_width;
	int m_height;
	std::string m_title;
	sf::RenderWindow *m_window;
	sf::Event m_event;
};
