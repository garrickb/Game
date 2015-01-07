#include "Game.h"
#include "GameObject.h"
#include "SpriteAnimation.h"
#include "BoxGameObject.h"

#include "StaticPhysicsComponent.h"

/*
 *	Create the game window and initalize the clock.
 */
void Game::init()
{
	m_window.create(m_width, m_height, m_title);

#ifdef DEBUG
	/* Initalize FPS Text */
	if (!fpsFont.loadFromFile("Resources/Fonts/OpenSans-Regular.ttf"))
		std::cout << "Error loading FPS Font." << std::endl;
	fpsText.setFont(fpsFont);
	fpsText.setCharacterSize(24);
	fpsText.setColor(sf::Color::Red);
#endif

	//Create Box2D World
	m_world = new World();
	/*
	TODO: Fixed Rotation Fix.

	*/

	std::vector<Component*> *comps = new std::vector<Component*>;

	//------------------------------------
	//TODO: Capsule Support for player.  |
	//------------------------------------

	//Player
	comps->push_back(new PlayerInputComponent());
	comps->push_back(new PlayerPhysicsComponent());
	objects.push_back(new AnimatedSpriteGameObject("player_idle", *comps));

	//Floor
	comps = new std::vector<Component*>;
	comps->push_back(new StaticPhysicsComponent());
	objects.push_back(new BoxGameObject(400, 575, 800, 50, *comps));

	//Wall
	comps = new std::vector<Component*>;
	comps->push_back(new StaticPhysicsComponent());
	objects.push_back(new BoxGameObject(775, 300, 50, 600, *comps));

	//128x128 box
	comps = new std::vector<Component*>;
	comps->push_back(new StaticPhysicsComponent(false));
	objects.push_back(new BoxGameObject(200, 486, 128, 128, *comps));

	//Rotating rectangle of doom
	comps = new std::vector<Component*>;
	comps->push_back(new StaticPhysicsComponent(true));
	objects.push_back(new BoxGameObject(400, 300, 25, 250, *comps));

	/* Dynamic Pyramid */

	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(500, 450, 50, 50, *comps));
	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(550, 450, 50, 50, *comps));
	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(600, 450, 50, 50, *comps));
	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(650, 450, 50, 50, *comps));

	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(525, 400, 50, 50, *comps));
	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(575, 400, 50, 50, *comps));
	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(600, 400, 50, 50, *comps));

	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(550, 350, 50, 50, *comps));
	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(600, 350, 50, 50, *comps));

	comps = new std::vector<Component*>;
	comps->push_back(new DynamicPhysicsComponent(true));
	objects.push_back(new BoxGameObject(575, 300, 50, 50, *comps));




	///* top */
	//objects.push_back(new BoxGameObject(575, 300, 50, 50,
	//	new InputComponent(),
	//	new DynamicPhysicsComponent()));
}

/*
*	Run the game until we recieve a request to exit.
*/
void Game::run()
{
	init();

	while (!m_window.isClosedRequested())
	{
		/* Reset Clock and get delta time. */
		m_time = m_clock.restart();

		/* Update the Window. */
		update();

		/* Render the Window. */
		render();
	}
}

/*
*	Update the window and run all game logic.
*/
void Game::update()
{
	/* Handle Window Events */
	m_window.update();


#ifdef DEBUG
	float currentFps = 1000000.f / m_time.asMicroseconds();

	fpsQueue.push(currentFps);

	/* Average FPS from a queue containing 60 FPS measurements. */
	if (fpsClock.getElapsedTime().asSeconds() >= fpsSampleRate)
	{
		fpsSampleSize = fpsQueue.size();
		fps = 0;
		while (!fpsQueue.empty())
		{
			fps += fpsQueue.front();
			fpsQueue.pop();
		}
		fpsClock.restart();
		fps /= fpsSampleSize;
		fpsText.setString("FPS: " + std::to_string((int)fps));
	}
#endif
	
	/* Handle Box2D Physics */

		m_world->box2DWorld->Step(m_time.asSeconds(), 25, 15);

		/* Update All Objects */
		for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		{
			(*it)->update(m_world);
		}
		m_stepTime = *new sf::Time;
	
}

/*
*	Render the graphics of the game.
*/
void Game::render()
{	
	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		if (*(it) && (*it)->body)
			(*it)->render(&m_window);
	}

#ifdef DEBUG
	/* Draw FPS */
	m_window.getSfWindow()->draw(fpsText);
#endif

	/* End current frame. */
	m_window.display();
}
