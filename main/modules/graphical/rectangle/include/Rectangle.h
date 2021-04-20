#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Color.h"
#include "Position.h"

using Float32 = float;
using Size = Position;
using UInt32 = unsigned int;
using Window = sf::RenderWindow;

class Rectangle
{
public:
  Rectangle();
  Rectangle(const Position& position,
            const Size& size,
            const Color& fill_color,
            Float32 thickness,
            const Color& thickness_color);

  void Draw(Window* window);
  void SetFillColor(const Color& color);
  void SetOutlineColor(const Color& color);
  void SetOutlineThickness(Float32 thickness);
  void SetPosition(const Position& position);
  void SetSize(const Size& size);

  const Color& SetFillColor() const;
  const Color& SetOutlineColor() const;
  Float32 SetOutlineThickness() const;
  const Position& SetPosition() const;
  const Size& SetSize() const;

private:
  sf::RectangleShape m_rectangle;
};
