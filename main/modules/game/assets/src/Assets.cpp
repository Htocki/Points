#include "Assets.h"

const Assets&
Assets::Instance()
{
  static Assets assets;
  return assets;
}

const sf::Font&
Assets::GetSansationFont() const
{
  return m_sansation_font;
}

Assets::Assets()
{
  if (!m_sansation_font.loadFromFile("media/fonts/Sansation.ttf")) {
    throw std::invalid_argument{
      "File \"media/fonts/Sansation.ttf\" not found."
    };
  }
}