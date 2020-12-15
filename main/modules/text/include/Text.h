#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

class Text {
 public:
  void Draw(sf::RenderWindow* window);
  
  void SetCharacterSize(unsigned int size);
  void SetFillColor(const sf::Color& color);
  void SetFont(const sf::Font& font);
  void SetPosition(const sf::Vector2f& position);
  void SetString(const sf::String& string);
  void SetStyle(sf::Uint32 style);
  
  unsigned int        GetCharacterSize() const;
  const sf::Color&    GetFillColor() const;
  const sf::Font*     GetFont() const;
  const sf::Vector2f& GetPosition() const;
  const sf::Vector2f  GetSize() const;
  const sf::String&   GetString() const;
  sf::Uint32          GetStyle() const;

 private:
  sf::Text m_text;
};
