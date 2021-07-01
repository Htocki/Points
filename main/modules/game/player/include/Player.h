#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

class Player
{
public:
  Player(const sf::String& name, sf::Color color, bool active);

  void Activate();
  void Deactivate();

  bool IsActive() const;

  sf::Color GetColor() const;
  const sf::String& GetName() const;

private:
  sf::String name_;
  sf::Color color_;
  bool active_;
};
