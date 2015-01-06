#include "Sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(std::string path)
	: m_path("Resources/Images/" + path)
{
	if (!loadTexture())
		exit(5);
	m_sprite.setTexture(*m_texture);
}

Sprite::Sprite(std::string path, int startX, int startY, int width, int height)
	: m_path("Resources/Images/" + path)
{
	if (!loadTexture())
		exit(5);
		m_sprite.setTexture(*m_texture);
	m_sprite.setTextureRect(sf::IntRect(startX, startY, width, height));
}

/*
* Used to overwrite an existing sprite.
*/
void Sprite::load(std::string path)
{
	if (m_path.length() != 0)
		remove();

	m_path = "Resources/Images/" + path;

	if (!loadTexture())
		exit(5);
	m_sprite.setTexture(*m_texture);
}

/*
* Used to overwrite an existing sprite.
*/
void Sprite::load(std::string path, int startX, int startY, int width, int height)
{
	if (m_path.length() != 0)
		remove();

	m_path = "Resources/Images/" + path;

	if (!loadTexture())
		exit(5);
	m_sprite.setTexture(*m_texture);
	m_sprite.setTextureRect(sf::IntRect(startX, startY, width, height));
}

/*
* Load the texture; we're assuming that 'm_path' has been set to the image location already.
*/
bool Sprite::loadTexture()
{
	//std::cout << "Loading: " << path << std::endl;

	if (m_path.length() == 0)
	{
		std::cerr << "Provided empty texture path!" << std::endl;
		return false;
	}

	/* Check if we've already loaded this particular image. */
	std::map<std::string, mapItem>::iterator it = loadedTextures.find(m_path);
	if (it == loadedTextures.end()) {
		std::cout << "Loading image for first time: " << m_path << std::endl;
		if (!loadedTextures[m_path].texture.loadFromFile(m_path))
		{
			std::cerr << "Failed to load image from path: " << m_path << std::endl;
			return false;
		}
		loadedTextures[m_path].count = 0;
		m_texture = &(loadedTextures[m_path].texture);
	} else {
		//std::cout << "Found texture in map already: " << it->first << std::endl;
		m_texture = &(it->second.texture);
	}

	++loadedTextures[m_path].count;

#ifdef DEBUG
	/* Print All File Paths We're Using */
	std::cout << "SPRITE COUNT DEBUG" << std::endl;
	for (auto const &it1 : loadedTextures)
	{
		std::cout << "\""<< it1.first << "\":\t" << it1.second.count << " reference(s)." << std::endl;
	}
	std::cout << "------------------------------------------------------------------------" << std::endl;
#endif
	return true;
}

void Sprite::render(Window* window)
{
	m_sprite.setRotation(m_rotation);
	window->getSfWindow()->draw(m_sprite);
}

void Sprite::update(World* world, float dTime) {}

/*
* Check to see if this is the last reference to the image; if it is, then we can remove the image from memory.
*/
void Sprite::remove()
{
	std::map<std::string, mapItem>::iterator it = loadedTextures.find(m_path);
	if (it != loadedTextures.end()) {
		--it->second.count;
		//If there are no more elements referencing to the texture, we can remove it.
		if (it->second.count == 0)
		{
			std::cout << "Removed last reference to " << m_path << "." << std::endl;
			loadedTextures.erase(it);
		}
		else {
			std::cout << "Removed sprite referencing " << m_path << ", there are now " << it->second.count << " references remaining." << std::endl;
		}
	}
}

Sprite::~Sprite()
{
	std::cout << "Sprite Deconstructed." << std::endl;
	remove();
}