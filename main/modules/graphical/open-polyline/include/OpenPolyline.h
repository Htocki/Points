#pragma once

#include <initializer_list>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Line.h"

class OpenPolyline
{
public:
  OpenPolyline(sf::Color color, float thickness);

  OpenPolyline(std::initializer_list<sf::Vector2f> nodes,
               sf::Color color,
               float thickness);

  virtual void Add(const sf::Vector2f& node);
  void Clear();
  void Remove(const sf::Vector2f& node);
  void SetColor(sf::Color color);
  void SetThickness(float thickness);

  const sf::Vector2f& At(unsigned int index) const;
  void Draw(sf::RenderWindow* window) const;
  sf::Color GetColor() const;
  float GetThickness() const;
  unsigned int NodesCount() const;

  bool IsEmpty() const;

private:
  std::vector<Line> lines_;
  std::vector<sf::Vector2f> nodes_;
  sf::Color color_;
  float thickness_;
};
