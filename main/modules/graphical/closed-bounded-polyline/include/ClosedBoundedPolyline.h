#pragma once

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Line.h"

class ClosedBoundedPolyline {
public:
  ClosedBoundedPolyline(unsigned int bounding_radius, float thickness);

  void AddNode(const sf::Vector2f& node, sf::Color color);
  void ToClear();

  const sf::Vector2f& At(unsigned int index) const;
  unsigned int        BoundingRadius() const;
  bool                Closed() const;
  sf::Color           Color() const;
  bool                Empted() const;
  unsigned int        NodesCount() const;
  float               Thickness() const;
  void                ToDraw(sf::RenderWindow* window) const;

private:
  sf::CircleShape           bounding_area_;
  std::vector<Line>         lines_;
  std::vector<sf::Vector2f> nodes_;
  float                     thickness_;
};
