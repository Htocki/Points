#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>

#include "Color.h"
#include "Position.h"
#include "Text.h"

using Event = sf::Event;
using Float32 = float;
using Font = sf::Font;
using Rectangle = sf::RectangleShape;
using Size = Position;
using String = sf::String;
using Style = sf::Uint32;
using UInt32 = unsigned int;
using Window = sf::RenderWindow;

class Button {
 public:
  void HandleEvent(const Event& event, const Window& window);
  void Draw(Window* window) const;

  void SetFillColor(const Color& color);
  void SetOutlineColor(const Color& color);
  void SetOutlineThickness(Float32 thickness);
  void SetPosition(const Position& position);
  void SetSize(const Size& size);
  void SetTextString(const String& string); 
  void SetTextCharacterSize(UInt32 size);
  void SetTextFillColor(const Color& color);
  void SetTextFont(const Font& font);
  void SetTextStyle(Style style);

  Color           GetFillColor() const;
  Color           GetOutlineColor() const;
  Float32         GetOutlineThickness() const;
  Position        GetPosition() const;
  Size            GetSize() const;
  const String&   GetTextString() const;
  UInt32          GetTextCharacterSize() const;
  Color           GetTextFillColor() const;
  const Font*     GetTextFont() const;
  Style           GetTextStyle() const;

 private:
  bool IsInside(const Position& position);
  bool IsInside(Float32 x, Float32 y);
  void SetTextInCenter(); 
 
  Rectangle m_background;
  Text m_text;
};
