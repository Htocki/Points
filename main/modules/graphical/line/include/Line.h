#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Line
{
public:
  Line(const sf::Vector2f& begin,
       const sf::Vector2f& end,
       sf::Color color,
       float thickness);

  void Draw(sf::RenderWindow* window) const;

  void SetBegin(const sf::Vector2f& begin);
  void SetColor(sf::Color color);
  void SetEnd(const sf::Vector2f& end);
  void SetThickness(float thickness);

  const sf::Vector2f& GetBegin() const;
  sf::Color GetColor() const;
  const sf::Vector2f& GetEnd() const;
  float GetThickness() const;

private:
  void SetVertexPositions(const sf::Vector2f& begin, const sf::Vector2f& end);

  sf::Vector2f begin_;
  sf::Vector2f end_;
  sf::Vector2f vertices_[4];
  sf::Color color_;
  float thickness_;
};
