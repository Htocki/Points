#pragma once

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
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

  sf::RenderWindow window_;
  Field field_;
  Player player1_;
  Player player2_;
  Indicator player1_indicator_;
  Indicator player2_indicator_;
  ClosedBoundedPolyline polyline_;
  std::vector<sf::ConvexShape> convexes_;
  bool step_;
};
