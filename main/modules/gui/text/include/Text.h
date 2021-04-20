#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>

#include "Color.h"
#include "Position.h"

using Font = sf::Font;
using Size = Position;
using String = sf::String;
using Style = sf::Uint32;
using UInt32 = unsigned int;
using Window = sf::RenderWindow;

class Text
{
public:
  void Draw(Window* window) const;

  void SetCharacterSize(UInt32 size);
  void SetFillColor(const Color& color);
  void SetFont(const Font& font);
  void SetPosition(const Position& position);
  void SetString(const String& string);
  void SetStyle(Style style);

  UInt32 GetCharacterSize() const;
  const Color GetFillColor() const;
  const Font* GetFont() const;
  const Position GetPosition() const;
  const Size GetSize() const;
  const String& GetString() const;
  Style GetStyle() const;

private:
  sf::Text m_text;
};
