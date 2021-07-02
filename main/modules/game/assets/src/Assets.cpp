#include "Assets.h"

const Assets& Assets::Instance() {
  static Assets assets;
  return assets;
}

const sf::Font& Assets::GetPixelFont7() const {
  return pixel_font7_;
}

Assets::Assets() {
  if (!pixel_font7_.loadFromFile("media/fonts/PixelFont7.ttf")) {
    throw std::invalid_argument("File \"media/fonts/PixelFont7.ttf\" not found.");
  }
}
