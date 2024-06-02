#include "Tips.h"
#include "Map.h"
#include <thread>
#include "Snake.h"
#include <iostream>

void Tips::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform = getTransform();
	target.draw(content);
}

Tips::Tips(std::string cont, sf::Vector2f position, std::function<void(Tips*)> deleteTips)
{
	font.loadFromFile("Content\\font\\StartMenuButton.ttf");
	content.setFont(font);
	content.setCharacterSize(20);
	content.setString(cont);
	sf::FloatRect textBounds = content.getLocalBounds();
	content.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	content.setPosition(position);

	std::thread t(&Tips::beginAnimation, this, deleteTips);
	t.detach();
}

void Tips::beginAnimation(std::function<void(Tips*)> deleteTips)
{
	sf::Clock clock;

	float a = content.getPosition().x;
	float initContY = content.getPosition().y;
	sf::Color color = content.getFillColor();

	while (clock.getElapsedTime().asSeconds() < 1.f) 
	{
		float fadtio = clock.getElapsedTime().asSeconds() / 1.f;
		content.setFillColor(sf::Color(color.r, color.g, color.b, fadtio * 255));
		content.setPosition(a, initContY - 30.f * fadtio);
	}

	initContY = content.getPosition().y;

	while (clock.getElapsedTime().asSeconds() < 2.f)
	{
		float fadtio = (clock.getElapsedTime().asSeconds() - 1.f) / 1.f;
		content.setFillColor(sf::Color(color.r, color.g, color.b, (1-fadtio) * 255));
	}

	deleteTips(this);
}
