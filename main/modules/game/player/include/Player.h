#pragma once

#include <SFML/System/String.hpp>

#include "Color.h"

class Player {
 public:
  Player(const sf::String& name, const Color& color, bool active);

  void Activate();
  void Deactivate();
  
  bool IsActive() const;

  const Color&  GetColor() const;
  const sf::String& GetName() const;

 private:
  sf::String name_;
  Color color_;
  bool active_;
};
