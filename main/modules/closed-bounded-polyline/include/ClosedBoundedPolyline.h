#pragma once

#include <array>
#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

#include "Line.h"

class ClosedBoundedPolyline {
 public:
  explicit ClosedBoundedPolyline(unsigned int bounding_radius, float thickness);

  void Draw(sf::RenderWindow* window) const;

  void AddPointPosition(const sf::Vector2f& position, const sf::Color& color);
  const sf::Vector2f& At(unsigned int index) const;
  void Clear();

  bool IsClosed() const;
  bool IsEmpty() const;

  unsigned int      GetBoundingRadius() const;
  const sf::Color&  GetColor() const;
  unsigned int      GetPointCount() const;
  float             GetThickness() const;

 private:
  std::vector<Line> lines_;
  std::vector<sf::Vector2f> positions_;
  sf::CircleShape bounding_area_;
  float thickness_;
};
