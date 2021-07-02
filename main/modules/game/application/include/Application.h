#pragma once

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "ClosedBoundedPolyline.h"
#include "Field.h"
#include "Indicator.h"
#include "Player.h"

class Application {
public:
  Application();
  void Run();

private:
  void HandleEvent(const sf::Event& event);
  void Draw();

  std::vector<sf::ConvexShape> convexes_;
  Field field_;
  Indicator indicator1_;
  Indicator indicator2_;
  Player player1_;
  Player player2_;
  ClosedBoundedPolyline polyline_;
  sf::Text score1_;
  sf::Text score2_;
  bool step_;
  sf::RenderWindow window_;
};
