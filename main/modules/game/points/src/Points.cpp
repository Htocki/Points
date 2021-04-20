#include "Points.h"

Points::Points(const sf::Vector2f& position,
               const sf::Vector2f& count,
               sf::Uint32 distance,
               sf::Uint32 radius,
               sf::Color color)
{
  points_.resize(count.x * count.y);

  std::size_t k{ 0 };
  for (sf::Uint32 i{ 0 }; i < count.x; ++i) {
    for (sf::Uint32 j{ 0 }; j < count.y; ++j) {
      points_.at(k).setPosition(position.x + i * distance - radius,
                                position.y + j * distance - radius);
      ++k;
    }
  }

  for (auto& point : points_) {
    point.setRadius(radius);
  }
  for (auto& point : points_) {
    point.setPointCount(150);
  }
  for (auto& point : points_) {
    point.setFillColor(color);
  }
}

void
Points::Draw(sf::RenderWindow* window) const
{
  for (const auto& point : points_) {
    if (point.getFillColor() != sf::Color::White) {
      window->draw(point);
    }
  }
}

bool
Points::IsContainsNotFilledPoint(const sf::Vector2f& position) const
{
  for (auto& point : points_) {
    if (point.getGlobalBounds().contains(position) &&
        point.getFillColor() == sf::Color::White) {
      return true;
    }
  }
  return false;
}

bool
Points::IsContainsPointWithColor(const sf::Vector2f& position,
                                 const sf::Color& color) const
{
  for (auto& point : points_) {
    if (point.getGlobalBounds().contains(position) &&
        point.getFillColor() == color) {
      return true;
    }
  }
  return false;
}

bool
Points::IsPointFounded(const sf::Vector2f& position,
                       const sf::Color& color) const
{
  for (auto& point : points_) {
    if (point.getGlobalBounds().contains(position) &&
        point.getFillColor() == color) {
      return true;
    }
  }
  return false;
}

void
Points::SetPointFillColor(const sf::Vector2f& position, const sf::Color& color)
{
  for (auto& point : points_) {
    if (point.getGlobalBounds().contains(position)) {
      if (point.getFillColor() == sf::Color::White) {
        point.setFillColor(color);
      }
    }
  }
}

const sf::CircleShape&
Points::GetPoint(const sf::Vector2f& position) const
{
  for (auto& point : points_) {
    if (point.getGlobalBounds().contains(position)) {
      return point;
    }
  }
  throw std::logic_error{ "Point not found." };
}
