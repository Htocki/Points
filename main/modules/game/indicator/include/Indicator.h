#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Indicator {
public:
  Indicator(const sf::Vector2f& position,
            const sf::Vector2f& size,
            const sf::Color& color,
            bool enabled);

  void Draw(sf::RenderWindow* window) const;

  void Enable();
  void Disable();

  bool IsEnabled() const;

private:
  bool enabled_;
  sf::RectangleShape rectangle_;
};
