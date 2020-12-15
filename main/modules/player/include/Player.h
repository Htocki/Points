#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>

class Player {
  public:
    Player(const sf::String& name, const sf::Color& color, bool active);

    void activate();
    void deactivate();
    bool isActive() const;

    const sf::Color& getColor() const;
    const sf::String& getName() const;

  private:
    sf::String name_;
    sf::Color color_;
    bool active_;
};
