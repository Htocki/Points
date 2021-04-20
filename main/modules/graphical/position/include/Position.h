#pragma once

struct Position
{
  Position();
  Position(float x, float y);

  float X() const;
  float Y() const;

private:
  float x_;
  float y_;
};

Position
operator+(Position left, Position right);
Position
operator-(Position left, Position right);
Position
operator*(Position position, float value);
Position
operator/(Position position, float value);

bool
operator==(Position left, Position right);
bool
operator!=(Position left, Position right);
