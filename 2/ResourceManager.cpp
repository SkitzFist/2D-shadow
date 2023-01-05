#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    loadDebug();
}

ResourceManager::~ResourceManager() {
    delete debugFont;
}


sf::Font* ResourceManager::getFont(Fonts font) {
    sf::Font* f = nullptr;
    switch (font) {
    case Fonts::debug:
        f = debugFont;
        break;
    default:
        break;
    }
    return f;
}

sf::Texture* ResourceManager::getTexture(Textures texture) {
    sf::Texture* t = nullptr;
    switch (texture) {
    case Textures::debug:
        //TODO:
        break;
    default:
        break;
    }
    return t;
}

sf::Texture* ResourceManager::loadTexture(const std::string& path) {
    sf::Texture* t = new sf::Texture();
    if (!t->loadFromFile(path)) {
        invalidPathError(path);
    }

    return t;
}

sf::Font* ResourceManager::loadFont(const std::string& path) {
    sf::Font* f = new sf::Font();
    if (!f->loadFromFile(path)) {
        invalidPathError(path);
    }

    return f;
}

void ResourceManager::invalidPathError(const std::string& path) const {
    throw std::runtime_error("Could not load" + path);
}

void ResourceManager::loadDebug() {
    std::string path = "../Bin/Fonts/PressStart.ttf";
    debugFont = loadFont(path);
}
