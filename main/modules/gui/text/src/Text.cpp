#include "Text.h"

void
Text::Draw(Window* window) const
{
  window->draw(m_text);
}

void
Text::SetCharacterSize(UInt32 size)
{
  m_text.setCharacterSize(size);
}

void
Text::SetFillColor(const Color& color)
{
  m_text.setFillColor({ color.R(), color.G(), color.B(), color.A() });
}

void
Text::SetFont(const Font& font)
{
  m_text.setFont(font);
}

void
Text::SetPosition(const Position& position)
{
  m_text.setPosition(position.X(), position.Y());
}

void
Text::SetString(const String& string)
{
  m_text.setString(string);
}

void
Text::SetStyle(Style style)
{
  m_text.setStyle(style);
}

UInt32
Text::GetCharacterSize() const
{
  return m_text.getCharacterSize();
}

const Color
Text::GetFillColor() const
{
  const auto color{ m_text.getFillColor() };
  return Color{ color.r, color.g, color.b, color.a };
}

const Font*
Text::GetFont() const
{
  return m_text.getFont();
}

const Position
Text::GetPosition() const
{
  const auto position{ m_text.getPosition() };
  return Position{ position.x, position.y };
}

const Size
Text::GetSize() const
{
  sf::FloatRect bounds{ m_text.getGlobalBounds() };
  return Size{ bounds.left + bounds.width, bounds.top + bounds.height };
}

const String&
Text::GetString() const
{
  return m_text.getString();
}

Style
Text::GetStyle() const
{
  return m_text.getStyle();
}
