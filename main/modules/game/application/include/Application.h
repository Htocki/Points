#pragma once

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Button.h"
#include "ClosedBoundedPolyline.h"
#include "Color.h"
#include "Grid.h"
#include "Indicator.h"
#include "Player.h"
#include "Points.h"
#include "Text.h"

sf::ConvexShape MakeConvex(const ClosedBoundedPolyline& polyline, const sf::Color& color);

class Application {
 public:
  Application();
  void Run();

 private:
  void HandleEvent(const sf::Event& event);
  void Draw();

  sf::RenderWindow window_;
  Grid grid_;
  Points points_;
  Player player1_;
  Player player2_;
  Indicator player1_indicator_;
  Indicator player2_indicator_;
  sf::CircleShape focus_;
  ClosedBoundedPolyline polyline_;
  std::vector<sf::ConvexShape> convexes_;
  bool step_;
};
