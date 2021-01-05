#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Line {
 public:
  Line(
    const sf::Vector2f& begin,
    const sf::Vector2f& end,
    const sf::Color& color,
    float thickness
  );

  void Draw(sf::RenderWindow* window) const;

  void SetBeginPosition(const sf::Vector2f& begin);
  void SetColor(const sf::Color& color);
  void SetEndPosition(const sf::Vector2f& end);
  void SetThickness(float thickness);

  const sf::Vector2f& GetBeginPosition() const;
  const sf::Color&    GetColor() const;
  const sf::Vector2f& GetEndPosition() const;
  float               GetThickness() const;

 private:
  void SetVertexPositions(const sf::Vector2f& being, const sf::Vector2f& end);
  void SetVerticesColor(const sf::Color& color);

  sf::Vector2f begin_;
  sf::Vector2f end_;
  sf::Vertex vertices_[4];
  sf::Color color_;
  float thickness_;
};
