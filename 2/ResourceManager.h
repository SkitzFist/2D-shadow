#pragma once
#include "SFML/Graphics.hpp"
enum class Textures {
	debug
};

enum class Fonts {
	debug
};

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();


	sf::Font* getFont(Fonts font);
	sf::Texture* getTexture(Textures texture);

private:
	sf::Texture* loadTexture(const std::string& path);
	sf::Font* loadFont(const std::string& path);
	void invalidPathError(const std::string& path) const;
	void loadDebug();

	sf::Font* debugFont;

};

