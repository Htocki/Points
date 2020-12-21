#include "Text.h"

void Text::Draw(sf::RenderWindow* window) const {
  window->draw(m_text);
}

void Text::SetCharacterSize(unsigned int size) {
  m_text.setCharacterSize(size);
}

void Text::SetFillColor(const sf::Color& color) {
  m_text.setFillColor(color);
}

void Text::SetFont(const sf::Font& font) {
  m_text.setFont(font);
}

void Text::SetPosition(const sf::Vector2f& position) {
  m_text.setPosition(position);
}

void Text::SetString(const sf::String& string) {
  m_text.setString(string);
}

void Text::SetStyle(sf::Uint32 style) {
  m_text.setStyle(style);
}

unsigned int Text::GetCharacterSize() const {
  return m_text.getCharacterSize();
}

const sf::Color& Text::GetFillColor() const {
  return m_text.getFillColor();
}

const sf::Font* Text::GetFont() const {
  return m_text.getFont();
}

const sf::Vector2f& Text::GetPosition() const {
  return m_text.getPosition();
}

const sf::Vector2f Text::GetSize() const {
  sf::FloatRect bounds { m_text.getGlobalBounds() };
  return sf::Vector2f { 
    bounds.left + bounds.width,
    bounds.top + bounds.height
  };
}

const sf::String& Text::GetString() const {
  return m_text.getString();
}

sf::Uint32 Text::GetStyle() const {
  return m_text.getStyle();
}
