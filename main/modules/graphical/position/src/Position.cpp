#include "Position.h"

Position::Position()
  : x_ { 0 }
  , y_ { 0 }
{}

Position::Position(float x, float y)
  : x_ { x }
  , y_ { y }
{}

float Position::X() const { return x_; }

float Position::Y() const { return y_; }

Position operator+(Position left, Position right) {
  return { left.X() + right.X(), left.Y() + right.Y() };
}

Position operator-(Position left, Position right) {
  return { left.X() - right.X(), left.Y() - right.Y() };
}

Position operator*(Position position, float value) {
  return { position.X() * value, position.Y() * value };
}

Position operator/(Position position, float value) {
  return { position.X() / value, position.Y() / value };
}

bool operator==(Position left, Position right) {
  return left.X() == right.X() && left.Y() == right.Y();
}

bool operator!=(Position left, Position right) {
  return !operator==(left, right);
}
