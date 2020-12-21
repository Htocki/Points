#include "Player.h"

Player::Player(const sf::String& name, const sf::Color& color, bool active)
  : name_ { name }
  , color_ { color }
  , active_ { active }
{}

void Player::activate() {
  active_ = true;
}

void Player::deactivate() {
  active_ = false;
}

bool Player::isActive() const {
  return active_;
}

const sf::Color& Player::getColor() const {
  return color_;
}

const sf::String& Player::getName() const {
  return name_;
}
