#pragma once
#include <SFML/Graphics.hpp>
#include <functional> // °üº¬ std::function

class mapPosition;
class Snake;

class Tips: public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font;
	sf::Text content;
public:
	Tips(std::string cont, sf::Vector2f position, std::function<void(Tips*)> deleteTips);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void beginAnimation(std::function<void(Tips*)> deleteTips);
};