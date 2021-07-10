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
  , color_ {color}
  , end_ {end}
  , thickness_ {thickness}
{
  SetVertexPositions(begin, end);
}

void Line::ToChangeBegin(const sf::Vector2f& begin) {
  SetVertexPositions(begin, end_);
  begin_ = begin;
}

void Line::ToChangeEnd(const sf::Vector2f& end) {
  SetVertexPositions(begin_, end);
  end_ = end;
}

void Line::ToChangeThickness(float thickness) {
  thickness_ = thickness;
}

void Line::ToRepaint(sf::Color color) {
  color_ = color;
}

const sf::Vector2f& Line::Begin() const {
  return begin_;
}

sf::Color Line::Color() const {
  return color_;
}

const sf::Vector2f& Line::End() const {
  return end_;
}

float Line::Thickness() const {
  return thickness_;
}

void Line::ToDraw(sf::RenderWindow* window) const {
  sf::Vertex vertices[4];
  for (unsigned int i {0}; i < 4; ++i) {
    vertices[i].position = sf::Vector2f {vertices_[i].x, vertices_[i].y};
  }
  for (unsigned int i {0}; i < 4; ++i) {
    vertices[i].color = sf::Color {color_};
  }
  window->draw(vertices, thickness_, sf::Quads);
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
