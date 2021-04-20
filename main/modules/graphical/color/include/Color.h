#pragma once

using UInt8 = unsigned char;

class Color
{
public:
  enum class Type
  {
    Black,
    Blue,
    Cyan,
    Gray,
    Green,
    Line,
    Magenta,
    Maroon,
    Navy,
    Olive,
    Purple,
    Red,
    Silver,
    Teal,
    Yellow,
    White
  };

  enum class Transparency
  {
    Invisible,
    Visible
  };

  Color();
  Color(Type type);
  Color(Type type, Transparency transparency);
  Color(UInt8 r, UInt8 g, UInt8 b, UInt8 a);

  void SetA(UInt8 a);
  void SetG(UInt8 b);
  void SetB(UInt8 g);
  void SetR(UInt8 r);
  void SetType(Type type);
  void SetType(UInt8 r, UInt8 g, UInt8 b);
  void SetTransparency(Transparency transparency);
  void SetTransparency(UInt8 a);

  UInt8 A() const;
  UInt8 B() const;
  UInt8 G() const;
  UInt8 R() const;

private:
  UInt8 a_;
  UInt8 b_;
  UInt8 g_;
  UInt8 r_;
};

bool
operator==(Color a, Color b);
bool
operator!=(Color a, Color b);
