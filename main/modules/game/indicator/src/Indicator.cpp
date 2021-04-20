#include "Indicator.h"

Indicator::Indicator(const sf::Vector2f& position,
                     const sf::Vector2f& size,
                     const sf::Color& color,
                     bool enabled)
  : enabled_{ enabled }
{
  rectangle_.setPosition(position);
  rectangle_.setSize(size);
  rectangle_.setOutlineColor(color);
  rectangle_.setOutlineThickness(3);
  if (IsEnabled()) {
    rectangle_.setFillColor(color);
  } else {
    rectangle_.setFillColor(sf::Color::White);
  }
}

void
Indicator::Enable()
{
  rectangle_.setFillColor(rectangle_.getOutlineColor());
  enabled_ = true;
}

void
Indicator::Disable()
{
  rectangle_.setFillColor(sf::Color::White);
  enabled_ = false;
}

bool
Indicator::IsEnabled() const
{
  return enabled_;
}

void
Indicator::Draw(sf::RenderWindow* window) const
{
  window->draw(rectangle_);
}
