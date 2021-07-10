#pragma once

#include <initializer_list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ClosedBoundedPolyline.h"

class BoundedPolygon : public ClosedBoundedPolyline {
public:
  BoundedPolygon(unsigned int bounding_radius, float thickness);

  void ToDraw(sf::RenderWindow* window) const;
};
