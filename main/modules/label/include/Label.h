#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

class Label {
 public:
  Label(const sf::Vector2f& position, const sf::String& string, const sf::Font& font,
        const sf::Color& color, unsigned int character_size, sf::Uint32 style);
  void draw(sf::RenderWindow* window) const;

 private:
  sf::Text text_;
};
