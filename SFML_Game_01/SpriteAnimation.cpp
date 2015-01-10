#include "SpriteAnimation.h"
#include <sstream>

SpriteAnimation::SpriteAnimation() {}

SpriteAnimation::SpriteAnimation(std::string path, bool repeat)
	: m_filepath("Resources/Animations/" + path + ".txt"), m_repeat(repeat)
{
	load();
}

/*
 * Load animation from .txt filepath specified.
 */
void SpriteAnimation::load()
{
	/* First let's check if the file path is valid. */
	if (m_filepath.size() == 0)
	{
		std::cerr << "Provided empty animation path!" << std::endl;
		return;
	}

	/* Check if we've already loaded this animation file. */
	std::map<std::string, animationMapItem>::iterator it = loadedAnimations.find(m_filepath);
	if (it == loadedAnimations.end()) {
		/* We're loading this animation .txt for the first time,
		 * or we loaded it already and erased it from the map. */
		float vertScale = 1.f;
		float horizScale = 1.f;
		std::ifstream animationFile(m_filepath);

		if (!animationFile)
		{
			std::cerr << "Error Reading Animation File: " << m_filepath << "." << std::endl;
		}
		else {

			std::string str;
			std::string imgPath;

			unsigned int i = 0;

			while (std::getline(animationFile, str))
			{
				int j = 0;
				std::stringstream ss(str);
				int tempCount = 0;
				switch (i)
				{
				case 0:
					imgPath = str;
					break;
				case 1:
					length = (float)atof((char*)str.c_str());
					break;
				default:
					/* First let's check for optional flip flags; then we'll
					 * check for the animation frames. */
					if (str == "flip_vert")
					{
						printf("Vert Flip\n");
						vertScale = -1.f;
						break;
					}
					else if (str == "flip_horiz")
					{
						printf("Horiz Flip\n");
						horizScale = -1.f;
						break;
					}
					int startX;
					int startY;
					int width;
					int height;
					while (ss >> j)
					{
						if (tempCount == 0)
							startX = j;
						else if (tempCount == 1)
							startY = j;
						else if (tempCount == 2)
							width = j;
						else if (tempCount == 3)
							height = j;
						else
							break;
						if (ss.peek() == ',')
							ss.ignore();
						++tempCount;
					}

					/* We want to store the maximum width and height out of all our sprites as our dimensions. */
					dimensions.x = dimensions.x > width ? dimensions.x : width;
					dimensions.y = dimensions.y > height ? dimensions.y : height;

					/* Make the sprite. */
					sprites.push_back(new Sprite(imgPath, startX, startY, width, height));
					sprites[sprites.size() - 1]->setOrigin(sf::Vector2f(width / 2.f, height / 2.f));
					sprites[sprites.size() - 1]->getSprite()->setScale(sf::Vector2f(horizScale, vertScale));
					break;
				}
				++i;
			}
		}

		/* If we failed to load the animation, show an error texture. */
		if (sprites.size() == 0)
		{
			dimensions.x = 64;
			dimensions.y = 64;
			sprites.push_back(new Sprite("error.png"));
			sprites[0]->setOrigin(sf::Vector2f(32, 32));
			std::cout << "Error loading: " << m_filepath << std::endl;
		}

		//We're done with the .txt file
		animationFile.close();

		/* Add to map of animations */
		animationMapItem item;
		item.data.length = length;
		item.data.dimensions = dimensions;
		item.data.sprites = sprites;
		item.count = 0;

		loadedAnimations[m_filepath] = item;
	} else {
		/* Animation was already found in the map. */
		length = it->second.data.length;
		dimensions = it->second.data.dimensions;
		sprites = it->second.data.sprites;
	}

	m_origin = sf::Vector2f(dimensions.x / 2.f, dimensions.y / 2.f);

	++loadedAnimations[m_filepath].count;

#ifdef DEBUG
	/* Print all the .txt files we're storing in our map, and many references towards them we have. */
	std::cout << "ANIMATED SPRITE COUNT DEBUG" << std::endl;
	for (auto const &it1 : loadedAnimations)
	{
		std::cout << "\"" << it1.first << "\":\t" << it1.second.count << " reference(s)." << std::endl;
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;
#endif

}

/*
* Load animation from .txt filepath specified.
* Only use this function if you used the default constructor with no provided file path.
*/
void SpriteAnimation::load(std::string filePath, bool repeat)
{
	m_repeat = repeat;
	m_filepath = filePath;
	if (m_filepath.length() != 0)
		remove();

	m_filepath = "Resources/Animations/" + filePath + ".txt";

	load();
}

/*
 * Update our animation frame depending on the animation length that was specified in the .txt file.
 */
void SpriteAnimation::update(World* world)
{
	if (length != 0)
		if (sprites.size() > 1 && m_clock.getElapsedTime().asSeconds() >= length / sprites.size())
		{
		/* Check if we're supposed to be repeating the animation. */
		if (m_repeat)
			++m_frame = m_frame % sprites.size();
		else if (m_frame != sprites.size() - 1)
				++m_frame;
			m_clock.restart();
		}
}

/*
* Render the correct sprite depending on our animation frame.
*/
void SpriteAnimation::render(Window* window)
{
	if (sprites.size() == 1)
		m_frame = 0;
	sprites[m_frame]->getSprite()->setPosition(m_position);
	sprites[m_frame]->setRotation(m_rotation);
	sprites[m_frame]->render(window);
}

/*
* Deconstructor.
*/
SpriteAnimation::~SpriteAnimation()
{
	if (m_filepath.size() != 0)
		remove();
}

/*
* If we're removing our last reference to this animation .txt file,
* let's remove it from the map to free up some memeory.
*/
void SpriteAnimation::remove()
{
	std::map<std::string, animationMapItem>::iterator it = loadedAnimations.find(m_filepath);
	if (it != loadedAnimations.end()) {
		--it->second.count;
		/* If there are no more elements referencing to the texture, we can remove it. */
		if (it->second.count == 0)
		{
			for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
				(*it)->remove();
		}
	}
}
