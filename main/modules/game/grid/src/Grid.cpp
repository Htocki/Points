#include "Grid.h"

Grid::Grid(const Position& position,
           const Position& size,
           unsigned int cell_size,
           const Color& color,
           float line_thickness)
{
  for (unsigned int i{ 0 }; i <= size.X(); ++i) {
    lines_.push_back(
      Line{ Position{ position.X() + i * cell_size, position.Y() },
            Position{ position.X() + i * cell_size,
                      position.Y() + size.Y() * cell_size },
            color,
            line_thickness });
  }

  for (unsigned int i{ 0 }; i <= size.Y(); ++i) {
    lines_.push_back(
      Line{ Position{ position.X(), position.Y() + i * cell_size },
            Position{ position.X() + size.X() * cell_size,
                      position.Y() + i * cell_size },
            color,
            line_thickness });
  }
}

void
Grid::Draw(sf::RenderWindow* window) const
{
  for (const auto& line : lines_) {
    line.Draw(window);
  }
}
