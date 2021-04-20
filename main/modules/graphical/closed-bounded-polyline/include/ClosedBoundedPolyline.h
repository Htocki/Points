#pragma once

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Color.h"
#include "Line.h"
#include "Position.h"

class ClosedBoundedPolyline
{
public:
  ClosedBoundedPolyline(unsigned int bounding_radius, float thickness);

  void Draw(sf::RenderWindow* window) const;

  void AddPointPosition(const Position& position, const Color& color);
  const Position& At(unsigned int index) const;
  void Clear();

  bool IsClosed() const;
  bool IsEmpty() const;

  unsigned int GetBoundingRadius() const;
  const Color& GetColor() const;
  unsigned int GetPointCount() const;
  float GetThickness() const;

private:
  std::vector<Line> lines_;
  std::vector<Position> positions_;
  sf::CircleShape bounding_area_;
  float thickness_;
};
