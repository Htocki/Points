#pragma once

#include <array>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Grid {
 public:
  Grid(const sf::Vector2f& position, const sf::Vector2f& size, sf::Uint32 cell_size, sf::Color color);
  void draw(sf::RenderWindow* window) const;

 private:
  std::vector<std::array<sf::Vertex, 2>> lines_;
};
