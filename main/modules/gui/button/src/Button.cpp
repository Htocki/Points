#include "Button.h"

void Button::HandleEvent(const Event& event, const Window& window) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (event.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f coords {
        window.mapPixelToCoords(sf::Mouse::getPosition(window))
      };
      if (IsInside(coords.x, coords.y)) {
        m_background.setOutlineColor(sf::Color::White);
        m_text.SetFillColor(Color::Type::White);
      }
    }
    if (event.mouseButton.button == sf::Mouse::Right) {
      sf::Vector2f coords {
        window.mapPixelToCoords(sf::Mouse::getPosition(window))
      };
      if (IsInside(coords.x, coords.y)) {
        m_background.setOutlineColor(sf::Color::Red);
        m_text.SetFillColor(Color::Type::Red);
      }
    }
  }
}

void Button::Draw(Window* window) const {
  window->draw(m_background);
  m_text.Draw(window);
}

void Button::SetFillColor(const Color& color) {
  m_background.setFillColor({
    color.R(), color.G(), color.B(), color.A()
  });
}

void Button::SetOutlineColor(const Color& color) {
  m_background.setOutlineColor({
    color.R(), color.G(), color.B(), color.A()
  });
}

void Button::SetOutlineThickness(Float32 thikness) {
  m_background.setOutlineThickness(thikness);
}

void Button::SetPosition(const Position& position) {
  m_background.setPosition(position.X(), position.Y());
  SetTextInCenter();
}

void Button::SetSize(const Size& size) {
  m_background.setSize({
    size.X(),
    size.X()
  });
}

void Button::SetTextString(const String& text) {
  m_text.SetString(text);
}

void Button::SetTextCharacterSize(UInt32 size) {
  m_text.SetCharacterSize(size);
}

void Button::SetTextFillColor(const Color& color) {
  m_text.SetFillColor(color);
}

void Button::SetTextFont(const Font& font) {
  m_text.SetFont(font);
}

void Button::SetTextStyle(Style style) {
  m_text.SetStyle(style);
}

Color Button::GetFillColor() const {
  const auto color { m_background.getFillColor() };
  return Color { color.r, color.g, color.b, color.a };
}

Color Button::GetOutlineColor() const {
  const auto color { m_background.getOutlineColor() };
  return Color {
    color.r, color.g, color.b, color.a
  };
}

Float32 Button::GetOutlineThickness() const {
  return m_background.getOutlineThickness();
}

Position Button::GetPosition() const {
  const auto position { m_background.getPosition() };
  return Position {
    position.x, position.y
  };
}

Size Button::GetSize() const {
  const auto size { m_background.getSize() };
  return Size { size.x, size.y };
}

const String& Button::GetTextString() const {
  return m_text.GetString();
}

UInt32 Button::GetTextCharacterSize() const {
  return m_text.GetCharacterSize();
}

Color Button::GetTextFillColor() const {
  return m_text.GetFillColor();
}

const Font* Button::GetTextFont() const {
  return m_text.GetFont();
}

UInt32 Button::GetTextStyle() const {
  return m_text.GetStyle();
}

bool Button::IsInside(const Position& position) {
  return m_background.getGlobalBounds().contains(position.X(), position.Y());
}

bool Button::IsInside(Float32 x, Float32 y) {
  return m_background.getGlobalBounds().contains(x, y);
}

void Button::SetTextInCenter() {
  m_text.SetPosition({
    GetPosition().X() + GetSize().X() / 2.f - m_text.GetSize().X() / 2.f,
    GetPosition().X() + GetSize().Y() / 2.f - m_text.GetSize().Y() / 2.f
  });
}
