#pragma once

#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Button.h"
#include "ClosedBoundedPolyline.h"
#include "Grid.h"
#include "Player.h"
#include "Points.h"
#include "Text.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Indicator {
  public:
    Indicator(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, bool enabled)
        : enabled_ { enabled }
    {
        rectangle_.setPosition(position);
        rectangle_.setSize(size);
        rectangle_.setOutlineColor(color);
        rectangle_.setOutlineThickness(3);
        if (isEnabled()) {
            rectangle_.setFillColor(color);
        } else {
            rectangle_.setFillColor(sf::Color::White);
        }
    }

    void enable() {
        rectangle_.setFillColor(rectangle_.getOutlineColor());
        enabled_ = true;
    }

    void disable() {
        rectangle_.setFillColor(sf::Color::White);
        enabled_ = false;
    }

    bool isEnabled() const { return enabled_; }

    void draw(sf::RenderWindow* window) const {
        window->draw(rectangle_);
    }

  private:
    bool enabled_;
    sf::RectangleShape rectangle_;
};

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
    Indicator player1_indicator_;
    Indicator player2_indicator_;
    Text player1_score_;
    Text player2_score_;
    sf::CircleShape focus_;
    ClosedBoundedPolyline polyline_;
    std::vector<sf::ConvexShape> convexes_;
    bool step_;
};
