#pragma once

#include <cstdint>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Line.h"
#include "Position.h"

using Size = Position;

class Grid
{
public:
  Grid(const Position& position,
       const Size& size,
       unsigned int cell_size,
       const Color& color,
       float line_thickness);

  void Draw(sf::RenderWindow* window) const;

private:
  std::vector<Line> lines_;
};
