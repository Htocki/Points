#pragma once

#include <initializer_list>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Color.h"
#include "Line.h"
#include "Position.h"

class OpenPolyline
{
public:
  OpenPolyline(const Color& color, float thickness);

  OpenPolyline(std::initializer_list<Position> nodes,
               const Color& color,
               float thickness);

  virtual void Add(const Position& node);
  void Clear();
  void Remove(const Position& node);
  void SetColor(const Color& color);
  void SetThickness(float thickness);

  const Position& At(unsigned int index) const;
  void Draw(sf::RenderWindow* window) const;
  const Color& GetColor() const;
  float GetThickness() const;
  unsigned int NodesCount() const;

  bool IsEmpty() const;

private:
  std::vector<Line> lines_;
  std::vector<Position> nodes_;
  Color color_;
  float thickness_;
};
