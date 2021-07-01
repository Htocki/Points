#pragma once

#include <initializer_list>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "OpenPolyline.h"

class ClosedPolyline : public OpenPolyline
{
public:
  ClosedPolyline(sf::Color color, float thickness);

  ClosedPolyline(std::initializer_list<sf::Vector2f> nodes,
                 sf::Color color,
                 float thickness);

  void Add(const sf::Vector2f& node) override;
};
