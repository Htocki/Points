#include "Color.h"

Color::Color()
  : a_ { 255 }
  , b_ { 0 }
  , g_ { 0 }
  , r_ { 0 }
{}

Color::Color(Type type)
  : a_ { 255 }
{
  SetType(type);
}

Color::Color(Type type, Transparency transparency)
{
  SetType(type);
  SetTransparency(transparency);
}

Color::Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a)
  : a_ { a }
  , b_ { b }
  , g_ { g }
  , r_ { r }
{}

void Color::SetA(UInt8 a) {
  a_ = a;
}

void Color::SetB(UInt8 b) {
  b_ = b;
}

void Color::SetG(UInt8 g) {
  g_ = g;
}

void Color::SetR(UInt8 r) {
  r_ = r;
}

void Color::SetType(Type type) {
  switch (type) {
    case Type::Black:
      SetR(0);
      SetG(0);
      SetB(0);
      break;

    case Type::Blue:
      SetR(0);
      SetG(0);
      SetB(255);
      break;

    case Type::Cyan:
      SetR(0);
      SetG(255);
      SetB(255);
      break;

    case Type::Gray:
      SetR(128);
      SetG(128);
      SetB(128);
      break;

    case Type::Green:
      SetR(0);
      SetG(128);
      SetB(0);
      break;

    case Type::Line:
      SetR(0);
      SetG(255);
      SetB(0);
      break;
    
    case Type::Magenta:
      SetR(255);
      SetG(0);
      SetB(255);
      break;

    case Type::Maroon:
      SetR(128);
      SetG(0);
      SetB(0);
      break;

    case Type::Navy:
      SetR(0);
      SetG(0);
      SetB(128);
      break;

    case Type::Olive:
      SetR(128);
      SetG(128);
      SetB(0);
      break;

    case Type::Purple:
      SetR(128);
      SetG(0);
      SetB(128);
      break;

    case Type::Red:
      SetR(255);
      SetG(0);
      SetB(0);
      break;

    case Type::Silver:
      SetR(192);
      SetG(192);
      SetB(192);
      break;

    case Type::Teal:
      SetR(0);
      SetG(128);
      SetB(128);
      break;

    case Type::White:
      SetR(255);
      SetG(255);
      SetB(255);
      break;

    case Type::Yellow:
      SetR(255);
      SetG(255);
      SetB(0);
      break;

    default:
      break;
  }
}

void Color::SetType(UInt8 r, UInt8 g, UInt8 b) {
  r_ = r;
  g_ = g;
  b_ = b;
}

void Color::SetTransparency(Transparency transparency) {
  switch (transparency) {
    case Transparency::Invisible:
      a_ = 0;
      break;

    case Transparency::Visible:
      a_ = 255;
      break;

    default:
      break;
  }
}

void Color::SetTransparency(UInt8 transparency) {
  a_ = transparency;
}

UInt8 Color::A() const {
  return a_;
}

UInt8 Color::B() const {
  return b_;
}

UInt8 Color::G() const {
  return g_;
}

UInt8 Color::R() const {
  return r_;
}

bool operator==(Color a, Color b) {
  return a.R() == b.R()
      && a.G() == b.G()
      && a.B() == b.B()
      && a.A() == b.A();
}

bool operator!=(Color a, Color b) {
  return !operator==(a, b);
}
