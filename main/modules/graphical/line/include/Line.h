#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Color.h"

class Line
{
public:
  Line(const sf::Vector2f& begin,
       const sf::Vector2f& end,
       const Color& color,
       float thickness);

  void Draw(sf::RenderWindow* window) const;

  void SetBegin(const sf::Vector2f& begin);
  void SetColor(const Color& color);
  void SetEnd(const sf::Vector2f& end);
  void SetThickness(float thickness);

  const sf::Vector2f& GetBegin() const;
  const Color& GetColor() const;
  const sf::Vector2f& GetEnd() const;
  float GetThickness() const;

private:
  void SetVertexPositions(const sf::Vector2f& begin, const sf::Vector2f& end);

  sf::Vector2f begin_;
  sf::Vector2f end_;
  sf::Vector2f vertices_[4];
  Color color_;
  float thickness_;
};
