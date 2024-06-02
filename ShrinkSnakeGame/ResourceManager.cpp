#include "ResourceManager.h"
#include <iostream>

void loadAndSetSprite(sf::Sprite& sprite, sf::Texture& texture, const std::string& filePath)
{
	//Set Game Icon info
	if (texture.loadFromFile(filePath)) {
		sprite.setTexture(texture);
		sf::FloatRect textBounds = sprite.getLocalBounds();
		sprite.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	}
	else {
		// 加载失败的处理
		std::cout << "Warning, load and set sprite faily" << std::endl;
	}
}

void AlignedCenterText(sf::Text& text)
{
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
}
