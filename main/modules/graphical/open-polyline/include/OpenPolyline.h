#pragma once

#include <initializer_list>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Line.h"

class OpenPolyline {
public:
  OpenPolyline(sf::Color color, float thickness);
  OpenPolyline(
    std::initializer_list<sf::Vector2f> nodes,
    sf::Color color,
    float thickness
  );

  virtual void  ToAdd(const sf::Vector2f& node);
  void          ToClear();
  void          ToRemove(const sf::Vector2f& node);
  void          ToRepaint(sf::Color color);
  void          ToChangeThickness(float thickness);

  const sf::Vector2f& At(unsigned int index) const;
  sf::Color           Color() const;
  bool                Empted() const;
  unsigned int        NodesCount() const;
  float               Thickness() const;
  void                ToDraw(sf::RenderWindow* window) const;

private:
  sf::Color                 color_;
  std::vector<Line>         lines_;
  std::vector<sf::Vector2f> nodes_;
  float                     thickness_;
};
