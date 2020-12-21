#include "Player.h"

Player::Player(const sf::String& name, const sf::Color& color, bool active)
  : name_ { name }
  , color_ { color }
  , active_ { active }
{}

void Player::Activate() {
  active_ = true;
}

void Player::Deactivate() {
  active_ = false;
}

bool Player::IsActive() const {
  return active_;
}

const sf::Color& Player::GetColor() const {
  return color_;
}

const sf::String& Player::GetName() const {
  return name_;
}
