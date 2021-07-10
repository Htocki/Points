#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Line {
public:
  Line(
    const sf::Vector2f& begin,
    const sf::Vector2f& end,
    sf::Color color,
    float thickness
  );

  void ToChangeBegin(const sf::Vector2f& begin);
  void ToChangeEnd(const sf::Vector2f& end);
  void ToChangeThickness(float thickness);
  void ToRepaint(sf::Color color);

  const sf::Vector2f& Begin() const;
  sf::Color           Color() const;
  const sf::Vector2f& End() const;
  float               Thickness() const;
  void                ToDraw(sf::RenderWindow* window) const;

private:
  void SetVertexPositions(const sf::Vector2f& begin, const sf::Vector2f& end);

  sf::Vector2f  begin_;
  sf::Color     color_;
  sf::Vector2f  end_;
  float         thickness_;
  sf::Vector2f  vertices_[4];
};
