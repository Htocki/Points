#pragma once

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "ClosedBoundedPolyline.h"
#include "Grid.h"
#include "Player.h"
#include "Points.h"

sf::ConvexShape MakeConvex(const ClosedBoundedPolyline& polyline, const sf::Color& color);

class Application {
  public:
    Application();
    void run();

  private:
    void handleEvent(const sf::Event& event);
    void draw();

    sf::RenderWindow window_;
    Grid grid_;
    Points points_;
    Player player1_;
    Player player2_;
    sf::CircleShape focus_;
    ClosedBoundedPolyline polyline_;
    std::vector<sf::ConvexShape> convexes_;
};
