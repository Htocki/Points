#include "Grid.h"

Grid::Grid(const sf::Vector2f& position, const sf::Vector2f& size, sf::Uint32 cell_size, sf::Color color) {
  for (sf::Uint32 i { 0 }; i <= size.x; ++i) {
    lines_.push_back({ 
      sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y), color), 
      sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y + size.y * cell_size), color)
    });
  }

  for (sf::Uint32 i { 0 }; i <= size.y; ++i) {
    lines_.push_back({
      sf::Vertex(sf::Vector2f(position.x, position.y + i * cell_size), color),
      sf::Vertex(sf::Vector2f(position.x + size.x * cell_size, position.y + i * cell_size), color)
    });
  }
}

void Grid::draw(sf::RenderWindow* window) const {
  for (const auto& line : lines_) {
    window->draw(line.data(), 2, sf::Lines);
  }
}
