#include "Label.h"

Label::Label(
    const sf::Vector2f& position, const sf::String& string, const sf::Font& font,
    const sf::Color& color, unsigned int character_size, sf::Uint32 style) 
{
    text_.setPosition(position);
    text_.setString(string);
    text_.setFont(font);
    text_.setFillColor(color);
    text_.setCharacterSize(character_size);
    text_.setStyle(style);
}

void Label::draw(sf::RenderWindow* window) const {
    window->draw(text_);
}
