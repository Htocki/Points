#include "Application.h"

#include <sstream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Assets.h"

sf::String toString(sf::Uint64 integer) {
  std::ostringstream os;
  os << integer;
  return os.str();
}

Application::Application()
  : field_ {sf::Vector2f{100.f, 90.f}, sf::Vector2f{30.f, 20.f}, 20, sf::Color::Black, 5}
  , indicator1_ {sf::Vector2f{220, 40}, sf::Vector2f{20, 20}, sf::Color::Red, true}
  , indicator2_ {sf::Vector2f{560, 40}, sf::Vector2f{20, 20}, sf::Color::Blue, false}
  , player1_ {sf::String{L"Игрок А"}, sf::Color::Red, true}
  , player2_ {sf::String{L"Игрок Б"}, sf::Color::Blue, false}
  , polygon_ {37, 4}
  , step_ {true}
  , window_ {sf::VideoMode{800, 600}, sf::String{L"ТО_oЧКИ"}, sf::Style::Default, sf::ContextSettings {0, 0, 8}}
{
  score1_.setFont(Assets::Instance().GetPixelFont7());
  score1_.setPosition(sf::Vector2f {100, 35});
  score1_.setString(player1_.GetName() + L": " + toString(player1_.GetScore()));
  score1_.setCharacterSize(20);
  score1_.setFillColor(sf::Color::Red);
  
  score2_.setFont(Assets::Instance().GetPixelFont7());
  score2_.setPosition(sf::Vector2f {600, 35});
  score2_.setString(player2_.GetName() + L": " + toString(player2_.GetScore()));
  score2_.setCharacterSize(20);
  score2_.setFillColor(sf::Color::Blue);
  
  window_.setFramerateLimit(70);
}

void Application::Run() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      HandleEvent(event);
      Draw();
    }
  }
}

void Application::HandleEvent(const sf::Event& event) {
  if (event.type == sf::Event::Closed) {
    window_.close();
  }

  sf::Vector2f coords {window_.mapPixelToCoords(sf::Mouse::getPosition(window_))};

  if (step_) {
    if (event.type == sf::Event::MouseButtonPressed) {
      sf::Color color {player1_.GetColor()};
      if (event.mouseButton.button == sf::Mouse::Left) {
        if (field_.setNodeColor(coords, color)) {
          indicator1_.Disable();
          indicator2_.Enable();
          player1_.Deactivate();
          player2_.Activate();
          polygon_.ToClear();
          step_ = false;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        if (field_.correctPosition(coords, color)) {
          polygon_.AddNode(coords, color);
          if (polygon_.Closed()) {
            polygons_.push_back(polygon_);
            polygon_.ToClear();
          }
        } else {
          polygon_.ToClear();
        }
      }
    }
  } else {
    if (event.type == sf::Event::MouseButtonPressed) {
      sf::Color color {player2_.GetColor()};
      if (event.mouseButton.button == sf::Mouse::Left) {
        if (field_.setNodeColor(coords, color)) {
          indicator1_.Enable();
          indicator2_.Disable();
          player1_.Activate();
          player2_.Deactivate();
          polygon_.ToClear();
          step_ = true;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        if (field_.correctPosition(coords, color)) {
          polygon_.AddNode(coords, color);
          if (polygon_.Closed()) {
            polygons_.push_back(polygon_);
            polygon_.ToClear();
          }
        } else {
          polygon_.ToClear();
        }
      }
    }
  }
}

void Application::Draw() {
  window_.clear(sf::Color::White);
  field_.draw(&window_);
  for (auto polygon : polygons_) { polygon.ToDraw(&window_); }
  polygon_.ToDraw(&window_);
  indicator1_.Draw(&window_);
  indicator2_.Draw(&window_);
  window_.draw(score1_);
  window_.draw(score2_);
  window_.display();
}
