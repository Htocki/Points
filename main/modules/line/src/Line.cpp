#include "Line.h"

#include <cmath>

Line::Line(
  const sf::Vector2f& begin,
  const sf::Vector2f& end,
  const sf::Color& color,
  float thickness
)
  : begin_ { begin }
  , end_ { end }
  , color_ { color }
  , thickness_ { thickness }
{
  SetVertexPositions(begin, end);
  SetVerticesColor(color);
}

void Line::Draw(sf::RenderWindow* window) const {
  window->draw(vertices_, thickness_, sf::Quads);
}

void Line::SetBeginPosition(const sf::Vector2f& begin) {
  SetVertexPositions(begin, end_);
  SetVerticesColor(color_);
  begin_ = begin;
}

void Line::SetEndPosition(const sf::Vector2f& end) {
  SetVertexPositions(begin_, end);
  SetVerticesColor(color_);
  end_ = end;
}

void Line::SetColor(const sf::Color& color) {
  SetVerticesColor(color);
  color_ = color;
}

void Line::SetThickness(float thickness) {
  thickness_ = thickness;
}

const sf::Vector2f& Line::GetBeginPosition() const {
  return begin_;
}

const sf::Vector2f& Line::GetEndPosition() const {
  return end_;
}

const sf::Color& Line::GetColor() const {
  return color_;
}

float Line::GetThickness() const {
  return thickness_;
}

void Line::SetVertexPositions(const sf::Vector2f& begin, const sf::Vector2f& end) {
  sf::Vector2f direction { end - begin };
  sf::Vector2f unit_direction { direction / std::sqrt(direction.x * direction.x + direction.y * direction.y) };
  sf::Vector2f unit_perpendicular { -unit_direction.y, unit_direction.x };
  sf::Vector2f offset { (thickness_ / 2.f) * unit_perpendicular };

  vertices_[0].position = begin + offset;
  vertices_[1].position = end + offset;
  vertices_[2].position = end - offset;
  vertices_[3].position = begin - offset;
}

void Line::SetVerticesColor(const sf::Color& color) {
  for (unsigned int i { 0 }; i < 4; ++i) {
    vertices_[i].color = color;
  }
}
