#include "Window.h"

Window::Window() {}


Window::~Window() {}

/*
*	Initalize the window and turn on VSync.
*/
void Window::create(int width, int height, std::string title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Vidya Game");
	m_window->setVerticalSyncEnabled(true);
}

int windowWidth = 800;
int windowHeight = 600;

/*
*	Poll the window for any new events.
*/
void Window::update()
{
	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_isCloseRequested = true;
			break;
		case sf::Event::Resized:
			windowWidth = m_event.size.width;
			windowHeight = m_event.size.height;
			m_window->setView(sf::View(sf::FloatRect(0,0,windowWidth,windowHeight)));
			m_window->setVerticalSyncEnabled(false);
			break;
		}
	}
}

/*
*	Display the window; this is the last thing we do in the rendering phase.
*/
void Window::display()
{
	m_window->display();
	m_window->clear(sf::Color::Black);
}