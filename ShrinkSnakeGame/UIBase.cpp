#include "UIBase.h"

void UIBase::setCursorType(sf::RenderWindow& nowWindow, sf::Cursor::Type type)
{
	sf::Cursor cursor;
	cursor.loadFromSystem(type);
	nowWindow.setMouseCursor(cursor);
}

UIBase::~UIBase()
{

}
