#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Color.h"
#include "Position.h"

class Line
{
public:
  Line(const Position& begin,
       const Position& end,
       const Color& color,
       float thickness);

  void Draw(sf::RenderWindow* window) const;

  void SetBegin(const Position& begin);
  void SetColor(const Color& color);
  void SetEnd(const Position& end);
  void SetThickness(float thickness);

  const Position& GetBegin() const;
  const Color& GetColor() const;
  const Position& GetEnd() const;
  float GetThickness() const;

private:
  void SetVertexPositions(const Position& begin, const Position& end);

  Position begin_;
  Position end_;
  Position vertices_[4];
  Color color_;
  float thickness_;
};
