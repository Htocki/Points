#pragma once

#include <SFML/Graphics/Font.hpp>

class Assets {
public:
  static const Assets& Instance();
  const sf::Font& GetPixelFont7() const;

private:
  sf::Font pixel_font7_;
  Assets();
  Assets(const Assets&) = delete;
  Assets& operator=(const Assets&) = delete;
};
