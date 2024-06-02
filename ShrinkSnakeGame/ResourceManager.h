#pragma once
#include <SFML/Graphics.hpp>

// 加载并设置图标资源,默认居中对其
void loadAndSetSprite(sf::Sprite& sprite, sf::Texture& texture, const std::string& filePath);

void AlignedCenterText(sf::Text& text);

