#include "Line.h"

#include <cmath>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>

Line::Line(
  const sf::Vector2f& begin,
  const sf::Vector2f& end,
  sf::Color color,
  float thickness
)
  : begin_ {begin}
  , end_ {end}
  , color_ {color}
  , thickness_ {thickness}
{
  SetVertexPositions(begin, end);
}

void Line::Draw(sf::RenderWindow* window) const {
  sf::Vertex vertices[4];

  for (unsigned int i {0}; i < 4; ++i) {
    vertices[i].position = { vertices_[i].x, vertices_[i].y };
  }

  for (unsigned int i {0}; i < 4; ++i) {
    vertices[i].color = { color_ };
  }
  window->draw(vertices, thickness_, sf::Quads);
}

void Line::SetBegin(const sf::Vector2f& begin) {
  SetVertexPositions(begin, end_);
  begin_ = begin;
}

void Line::SetEnd(const sf::Vector2f& end) {
  SetVertexPositions(begin_, end);
  end_ = end;
}

void Line::SetColor(sf::Color color) {
  color_ = color;
}

void Line::SetThickness(float thickness) {
  thickness_ = thickness;
}

const sf::Vector2f& Line::GetBegin() const {
  return begin_;
}

const sf::Vector2f& Line::GetEnd() const {
  return end_;
}

sf::Color Line::GetColor() const {
  return color_;
}

float Line::GetThickness() const {
  return thickness_;
}

void Line::SetVertexPositions(const sf::Vector2f& begin, const sf::Vector2f& end) {
  sf::Vector2f direction {end - begin};
  sf::Vector2f unit_direction {
    direction / std::sqrt(direction.x * direction.x + direction.y * direction.y)
  };
  sf::Vector2f unit_perpendicular {-unit_direction.y, unit_direction.x};
  sf::Vector2f offset {unit_perpendicular * (thickness_ / 2.f)};

  vertices_[0] = begin + offset;
  vertices_[1] = end + offset;
  vertices_[2] = end - offset;
  vertices_[3] = begin - offset;
}
