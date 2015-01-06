#include "SpriteAnimation.h"
#include <sstream>

SpriteAnimation::SpriteAnimation() {
	// std::cout << "Default SpriteAnimation Instantiated." << std::endl; 
}

SpriteAnimation::SpriteAnimation(std::string path, bool repeat)
	: m_filepath("Resources/Animations/" + path + ".txt"), m_repeat(repeat)
{
	//std::cout << "SpriteAnimation Instantiated." << std::endl;
	load();
}

/*
 * Load animation from .txt filepath specified.
 */
void SpriteAnimation::load()
{
	std::cout << "LOADING ANIMATIION." << m_filepath << std::endl;
	if (m_filepath.size() == 0)
	{
		std::cerr << "Provided empty animation path!" << std::endl;
		return;
	}
	/* Check if we've already loaded this animation file. */
	std::map<std::string, animationMapItem>::iterator it = loadedAnimations.find(m_filepath);
	if (it == loadedAnimations.end()) {

		std::cout << "Loading animation for the first time: " << m_filepath << std::endl;

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

					//Find the maximum height and width as our dimensions.
					dimensions.x = dimensions.x > width ? dimensions.x : width;
					dimensions.y = dimensions.y > height ? dimensions.y : height;

					//make sprite
					sprites.push_back(new Sprite(imgPath, startX, startY, width, height));
					sprites[sprites.size() - 1]->setOrigin(sf::Vector2f(width / 2, height / 2));
					break;
				}
				++i;
			}
		}
		if (sprites.size() == 0)
		{
			dimensions.x = 64;
			dimensions.y = 64;
			sprites.push_back(new Sprite("error.png"));
			sprites[0]->setOrigin(sf::Vector2f(32, 32));
		}
		animationFile.close();
		//std::cout << "Sprite Count: " << sprites.size() << std::endl;

		/* Add to map of animations */
		animationMapItem item;
		item.data.length = length;
		item.data.dimensions = dimensions;
		item.data.sprites = sprites;
		item.count = 0;

		loadedAnimations[m_filepath] = item;
	} else {
		std::cout << "Found animation in map already: " << it->first << std::endl;
		length = it->second.data.length;
		dimensions = it->second.data.dimensions;
		sprites = it->second.data.sprites;
	}

	m_origin = sf::Vector2f(dimensions.x / 2, dimensions.y / 2);

	++loadedAnimations[m_filepath].count;

#ifdef DEBUG
	/* Print All File Paths We're Using */
	std::cout << "ANIMATED SPRITE COUNT DEBUG" << std::endl;
	for (auto const &it1 : loadedAnimations)
	{
		std::cout << "\"" << it1.first << "\":\t" << it1.second.count << " reference(s)." << std::endl;
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;
#endif

}

void SpriteAnimation::load(std::string filePath)
{
	m_filepath = filePath;
	if (m_filepath.length() != 0)
		remove();

	m_filepath = "Resources/Animations/" + filePath + ".txt";

	load();
}

void SpriteAnimation::update(World* world, float dTime)
{
	//std::cout << m_clock.getElapsedTime().asSeconds() << "/" << length << std::endl;
	if (length != 0)
		if (sprites.size() > 0 && m_clock.getElapsedTime().asSeconds() >= length / sprites.size())
		{
		++m_frame = m_frame % sprites.size();
		m_clock.restart();
		}
	//std::cout << "SpriteAnimation UPDATE" << std::endl;
}

void SpriteAnimation::render(Window* window)
{
	if (sprites.size() == 1)
		m_frame = 0;
	sprites[m_frame]->getSprite()->setPosition(m_position);
	sprites[m_frame]->setRotation(m_rotation);
	sprites[m_frame]->render(window);
}

SpriteAnimation::~SpriteAnimation()
{
	std::cout << "SpriteAnimation Deconstructed." << std::endl;
	if (m_filepath.size() != 0)
		remove();
}

void SpriteAnimation::remove()
{
	std::map<std::string, animationMapItem>::iterator it = loadedAnimations.find(m_filepath);
	if (it != loadedAnimations.end()) {
		--it->second.count;
		//If there are no more elements referencing to the texture, we can remove it.
		if (it->second.count == 0)
		{
			std::cout << "SPRITEANIMATION: Removed last reference to " << m_filepath << "." << std::endl;
			for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
				(*it)->remove();
		}
		else {
			std::cout << "Removed sprite referencing " << m_filepath << ", there are now " << it->second.count << " references remaining." << std::endl;
		}
	}
}
