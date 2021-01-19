#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Points {
 public:
  Points(const sf::Vector2f& position, const sf::Vector2f& count, sf::Uint32 distance, sf::Uint32 radius, sf::Color color);

  void Draw(sf::RenderWindow* window) const;

  bool IsContainsNotFilledPoint(const sf::Vector2f& position) const;
  bool IsContainsPointWithColor(const sf::Vector2f& position, const sf::Color& color) const;
  bool IsPointFounded(const sf::Vector2f& position, const sf::Color& color = sf::Color::White) const;

  void SetPointFillColor(const sf::Vector2f& position, const sf::Color& color);
  
  const sf::CircleShape& GetPoint(const sf::Vector2f& position) const;

 private:
  std::vector<sf::CircleShape> points_;
};
