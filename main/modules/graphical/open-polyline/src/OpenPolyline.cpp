#include "OpenPolyline.h"

#include <algorithm>

OpenPolyline::OpenPolyline(const Color& color, float thickness)
  : color_{ color }
  , thickness_{ thickness }
{}

OpenPolyline::OpenPolyline(std::initializer_list<Position> nodes,
                           const Color& color,
                           float thickness)
  : color_{ color }
  , thickness_{ thickness }
{
  for (const auto& node : nodes) {
    Add(node);
  }
}

void
OpenPolyline::Add(const Position& node)
{
  if (nodes_.size() < 1) {
    nodes_.push_back(node);
  } else {
    nodes_.push_back(node);
    lines_.push_back(Line{ Position{ nodes_.at(nodes_.size() - 2) },
                           Position{ nodes_.at(nodes_.size() - 1) },
                           color_,
                           thickness_ });
  }
}

void
OpenPolyline::Clear()
{
  lines_.clear();
  nodes_.clear();
}

void
OpenPolyline::Remove(const Position& node)
{
  const auto new_end{ std::remove(std::begin(nodes_), std::end(nodes_), node) };
  nodes_.erase(new_end, std::end(nodes_));
}

void
OpenPolyline::SetColor(const Color& color)
{
  color_ = color;
}

void
OpenPolyline::SetThickness(float thickness)
{
  thickness_ = thickness;
}

const Position&
OpenPolyline::At(unsigned int index) const
{
  return nodes_.at(index);
}

void
OpenPolyline::Draw(sf::RenderWindow* window) const
{
  for (auto& line : lines_) {
    line.Draw(window);
  }
}

const Color&
OpenPolyline::GetColor() const
{
  return color_;
}

float
OpenPolyline::GetThickness() const
{
  return thickness_;
}

unsigned int
OpenPolyline::NodesCount() const
{
  return nodes_.size();
}

bool
OpenPolyline::IsEmpty() const
{
  if (nodes_.size() > 0) {
    return false;
  }
  return true;
}
