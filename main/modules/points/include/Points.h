#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Points {
 public:
  Points(const sf::Vector2f& position, const sf::Vector2f& count, sf::Uint32 distance, sf::Uint32 radius, sf::Color color);
  void setPointFillColor(const sf::Vector2f& position, const sf::Color& color);
  bool isContainsNotFilledPoint(const sf::Vector2f& position) const;
  bool isContainsPointWithColor(const sf::Vector2f& position, const sf::Color& color) const;
  bool isPointFounded(const sf::Vector2f& position, const sf::Color& color = sf::Color::White) const;
  const sf::CircleShape& getPoint(const sf::Vector2f& position) const;
  void draw(sf::RenderWindow* window) const;

 private:
  std::vector<sf::CircleShape> points_;
};
