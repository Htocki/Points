#include "Button.h"

void Button::HandleEvent(const sf::Event& event, const sf::RenderWindow& window) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f coords { window.mapPixelToCoords(sf::Mouse::getPosition(window)) };
      if (IsInside(coords)) {
        m_background.setOutlineColor(sf::Color::White);
        m_text.SetFillColor(sf::Color::White);
      }
    }
    if (event.mouseButton.button == sf::Mouse::Right) {
      sf::Vector2f coords { window.mapPixelToCoords(sf::Mouse::getPosition(window)) };
      if (IsInside(coords)) {
        m_background.setOutlineColor(sf::Color::Red);
        m_text.SetFillColor(sf::Color::Red);
      }
    }
  }
}

void Button::Draw(sf::RenderWindow* window) const {
  window->draw(m_background);
  m_text.Draw(window);
}

void Button::SetFillColor(const sf::Color& color) {
  m_background.setFillColor(color);
}

void Button::SetOutlineColor(const sf::Color& color) {
  m_background.setOutlineColor(color);
}

void Button::SetOutlineThickness(float thikness) {
  m_background.setOutlineThickness(thikness);
}

void Button::SetPosition(const sf::Vector2f& position) {
  m_background.setPosition(position);
  SetTextInCenter();
}

void Button::SetSize(const sf::Vector2f& size) {
  m_background.setSize(size);
}

void Button::SetTextString(const sf::String& text) {
  m_text.SetString(text);
}

void Button::SetTextCharacterSize(unsigned int size) {
  m_text.SetCharacterSize(size);
}

void Button::SetTextFillColor(const sf::Color& color) {
  m_text.SetFillColor(color);
}

void Button::SetTextFont(const sf::Font& font) {
  m_text.SetFont(font);
}

void Button::SetTextStyle(sf::Uint32 style) {
  m_text.SetStyle(style);
}

const sf::Color& Button::GetFillColor() const {
  return m_background.getFillColor();
}

const sf::Color& Button::GetOutlineColor() const {
  return m_background.getOutlineColor();
}

float Button::GetOutlineThickness() const {
  return m_background.getOutlineThickness();
}

const sf::Vector2f& Button::GetPosition() const {
  return m_background.getPosition();
}

const sf::Vector2f& Button::GetSize() const {
  return m_background.getSize();
}

const sf::String& Button::GetTextString() const {
  return m_text.GetString();
}

unsigned int Button::GetTextCharacterSize() const {
  return m_text.GetCharacterSize();
}

const sf::Color& Button::GetTextFillColor() const {
  return m_text.GetFillColor();
}

const sf::Font* Button::GetTextFont() const {
  return m_text.GetFont();
}

sf::Uint32 Button::GetTextStyle() const {
  return m_text.GetStyle();
}

bool Button::IsInside(const sf::Vector2f& position) {
  return m_background.getGlobalBounds().contains(position);
}

void Button::SetTextInCenter() {
  m_text.SetPosition(sf::Vector2f {
    GetPosition().x + GetSize().x / 2.f - m_text.GetSize().x / 2.f,
    GetPosition().y + GetSize().y / 2.f - m_text.GetSize().y / 2.f
  });
}
