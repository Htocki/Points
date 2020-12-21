#pragma once

#include <array>
#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

class ClosedBoundedPolyline {
 public:
  explicit ClosedBoundedPolyline(unsigned int bounding_radius);
  void addPointPosition(const sf::Vector2f& position, const sf::Color& color);
  void draw(sf::RenderWindow* window) const;
  bool isClosed() const;
  bool isEmpty() const;
  unsigned int getPointCount() const;
  const sf::Vector2f& at(unsigned int index) const;
  void clear();

 private:
  std::vector<std::array<sf::Vertex, 2>> lines_;
  std::vector<sf::Vector2f> positions_;
  sf::CircleShape bounding_area_;
};
