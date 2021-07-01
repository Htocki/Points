#include "ClosedBoundedPolyline.h"

ClosedBoundedPolyline::ClosedBoundedPolyline(unsigned int bounding_radius,
                                             float thickness)
  : thickness_{ thickness }
{
  bounding_area_.setRadius(bounding_radius);
}

void
ClosedBoundedPolyline::Draw(sf::RenderWindow* window) const
{
  for (auto& line : lines_) {
    line.Draw(window);
  }
}

const sf::Vector2f&
ClosedBoundedPolyline::At(unsigned int index) const
{
  return positions_.at(index);
}

void
ClosedBoundedPolyline::Clear()
{
  lines_.clear();
  positions_.clear();
}

void
ClosedBoundedPolyline::AddPointPosition(const sf::Vector2f& position,
                                        sf::Color color)
{
  if (positions_.size() < 1) {
    positions_.push_back(position);
    bounding_area_.setPosition(position.x - bounding_area_.getRadius(),
                               position.y - bounding_area_.getRadius());
  } else {
    if (bounding_area_.getGlobalBounds().contains(position.x, position.y)) {
      positions_.push_back(position);
      bounding_area_.setPosition(position.x - bounding_area_.getRadius(),
                                 position.y - bounding_area_.getRadius());
      lines_.push_back(Line{ sf::Vector2f{ positions_.at(positions_.size() - 2) },
                             sf::Vector2f{ positions_.at(positions_.size() - 1) },
                             color,
                             thickness_ });
    } else {
      positions_.clear();
      lines_.clear();
    }
  }
}

bool
ClosedBoundedPolyline::IsClosed() const
{
  if (positions_.size() > 2) {
    if (positions_.at(0) == positions_.at(positions_.size() - 1)) {
      return true;
    }
  }
  return false;
}

bool
ClosedBoundedPolyline::IsEmpty() const
{
  if (positions_.size() > 0) {
    return false;
  }
  return true;
}

unsigned int
ClosedBoundedPolyline::GetPointCount() const
{
  return positions_.size();
}

sf::Color ClosedBoundedPolyline::GetColor() const {
  return lines_[0].GetColor();
}

float
ClosedBoundedPolyline::GetThickness() const
{
  return thickness_;
}

unsigned int
ClosedBoundedPolyline::GetBoundingRadius() const
{
  return bounding_area_.getRadius();
}
