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

  void Draw(sf::RenderWindow* window) const;

  void AddPointPosition(const sf::Vector2f& position, const sf::Color& color);
  const sf::Vector2f& At(unsigned int index) const;
  void Clear();

  bool IsClosed() const;
  bool IsEmpty() const;

  unsigned int GetPointCount() const;

 private:
  std::vector<std::array<sf::Vertex, 2>> lines_;
  std::vector<sf::Vector2f> positions_;
  sf::CircleShape bounding_area_;
};
