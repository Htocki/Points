#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

class Player {
public:
  // Инициализирующие
  Player(const sf::String& name, sf::Color color, bool state);
  
  // Модифицирующие
  void Activate();
  void Deactivate();
  void IncreaseScoreBy(sf::Uint64 value);
  void SetScoreToZero();
  
  // Немодифицирующие
  sf::Color         GetColor() const;
  const sf::String& GetName() const;
  sf::Uint64        GetScore() const;
  bool              IsActive() const;

private:
  bool        state_;
  sf::Color   color_;
  sf::String  name_;
  sf::Uint64  score_;
};