#include "OpenPolyline.h"

#include <algorithm>

OpenPolyline::OpenPolyline(sf::Color color, float thickness)
  : color_{ color }
  , thickness_{ thickness }
{}

OpenPolyline::OpenPolyline(std::initializer_list<sf::Vector2f> nodes,
                           sf::Color color,
                           float thickness)
  : color_{ color }
  , thickness_{ thickness }
{
  for (const auto& node : nodes) {
    Add(node);
  }
}

void
OpenPolyline::Add(const sf::Vector2f& node)
{
  if (nodes_.size() < 1) {
    nodes_.push_back(node);
  } else {
    nodes_.push_back(node);
    lines_.push_back(Line{ sf::Vector2f{ nodes_.at(nodes_.size() - 2) },
                           sf::Vector2f{ nodes_.at(nodes_.size() - 1) },
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
OpenPolyline::Remove(const sf::Vector2f& node)
{
  const auto new_end{ std::remove(std::begin(nodes_), std::end(nodes_), node) };
  nodes_.erase(new_end, std::end(nodes_));
}

void OpenPolyline::SetColor(sf::Color color) {
  color_ = color;
}

void
OpenPolyline::SetThickness(float thickness)
{
  thickness_ = thickness;
}

const sf::Vector2f&
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

sf::Color OpenPolyline::GetColor() const {
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
