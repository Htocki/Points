#pragma once

#include <SFML/Graphics/Font.hpp>

class Assets {
  public:
    static const Assets& instance();
    const sf::Font& getSansationFont() const;

  private:
    sf::Font m_sansation_font;

    Assets();
    Assets(const Assets&) = delete;
    Assets &operator=(const Assets&) = delete;
};
