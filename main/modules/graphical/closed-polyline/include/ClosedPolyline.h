#pragma once

#include <initializer_list>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Color.h"
#include "OpenPolyline.h"
#include "Position.h"

class ClosedPolyline : public OpenPolyline {
 public:
  ClosedPolyline(
    const Color& color,
    float thickness
  );

  ClosedPolyline(
    std::initializer_list<Position> nodes,
    const Color& color,
    float thickness
  );
  
  void Add(const Position& node) override;
};
