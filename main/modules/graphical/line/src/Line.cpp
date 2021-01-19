#include "Line.h"

#include <cmath>

#include <SFML/Graphics/Vertex.hpp>

Line::Line(
  const Position& begin,
  const Position& end,
  const Color& color,
  float thickness
)
  : begin_ { begin }
  , end_ { end }
  , color_ { color }
  , thickness_ { thickness }
{
  SetVertexPositions(begin, end);
}

void Line::Draw(sf::RenderWindow* window) const {
  sf::Vertex vertices[4];
  
  for (unsigned int i { 0 }; i < 4; ++i) {
    vertices[i].position = { vertices_[i].X(), vertices_[i].Y() };
  }
  
  for (unsigned int i { 0 }; i < 4; ++i) {
    vertices[i].color = { color_.R(), color_.G(), color_.B(), color_.A() };
  }
  window->draw(vertices, thickness_, sf::Quads);
}

void Line::SetBegin(const Position& begin) {
  SetVertexPositions(begin, end_);
  begin_ = begin;
}

void Line::SetEnd(const Position& end) {
  SetVertexPositions(begin_, end);
  end_ = end;
}

void Line::SetColor(const Color& color) {
  color_ = color;
}

void Line::SetThickness(float thickness) {
  thickness_ = thickness;
}

const Position& Line::GetBegin() const {
  return begin_;
}

const Position& Line::GetEnd() const {
  return end_;
}

const Color& Line::GetColor() const {
  return color_;
}

float Line::GetThickness() const {
  return thickness_;
}

void Line::SetVertexPositions(const Position& begin, const Position& end) {
  Position direction { end - begin };
  Position unit_direction {
    direction /
    std::sqrt(direction.X() * direction.X() + direction.Y() * direction.Y())
  };
  Position unit_perpendicular { -unit_direction.Y(), unit_direction.X() };
  Position offset { unit_perpendicular * (thickness_ / 2.f) };

  vertices_[0] = begin + offset;
  vertices_[1] = end + offset;
  vertices_[2] = end - offset;
  vertices_[3] = begin - offset;
}
