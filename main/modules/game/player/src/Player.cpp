#include "Player.h"

Player::Player(const sf::String& name, sf::Color color, bool state)
  : state_ {state}
  , color_ {color}
  , name_ {name}
{
  score_ = 0;
}

void Player::Activate() {
  state_ = true;
}

void Player::Deactivate() {
  state_ = false;
}

void Player::IncreaseScoreBy(sf::Uint64 value) {
  score_ += value;
}

void Player::SetScoreToZero() {
  score_ = 0;
}

sf::Color Player::GetColor() const {
  return color_;
}

const sf::String& Player::GetName() const {
  return name_;
}

sf::Uint64 Player::GetScore() const {
  return score_;
}

bool Player::IsActive() const {
  return state_;
}