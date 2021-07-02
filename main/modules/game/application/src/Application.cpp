#include "Application.h"

#include <sstream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Assets.h"

sf::ConvexShape MakeConvex(
  const ClosedBoundedPolyline& polyline,
  sf::Color color,
  float thickness
) {
  sf::ConvexShape convex;
  convex.setOutlineColor(color);
  convex.setOutlineThickness(thickness);
  color.a = 125;
  convex.setFillColor(color);
  convex.setPointCount(polyline.GetPointCount());
  for (unsigned int i {0}; i < polyline.GetPointCount(); ++i) {
    convex.setPoint(i, sf::Vector2f(polyline.At(i).x, polyline.At(i).y));
  }
  return convex;
}

sf::String toString(sf::Uint64 integer)
{
    std::ostringstream os;
    os << integer;
    return os.str();
}

Application::Application()
  : field_ {sf::Vector2f{100.f, 90.f}, sf::Vector2f{30.f, 20.f}, 20, sf::Color::Black, 5}
  , indicator1_ {sf::Vector2f{220, 40}, sf::Vector2f{20, 20}, sf::Color::Red, true}
  , indicator2_ {sf::Vector2f{560, 40}, sf::Vector2f{20, 20}, sf::Color::Blue, false}
  , player1_ {sf::String{L"Игрок А"}, sf::Color::Red, true}
  , player2_ {sf::String{L"Игрок Б"}, sf::Color::Blue, false}, polyline_ {37, 4}
  , step_ {true}
  , window_ {sf::VideoMode{800, 600}, sf::String{L"ТОЧКИ"}, sf::Style::Default, sf::ContextSettings{0, 0, 8}}
{
  score1_.setFont(Assets::Instance().GetPixelFont7());
  score1_.setPosition(sf::Vector2f {100, 35});
  score1_.setString(player1_.GetName() + L": " + toString(player1_.GetScore()));
  score1_.setCharacterSize(20);
  score1_.setFillColor(sf::Color::Red);
  score1_.setStyle(sf::Text::Bold);
  
  score2_.setFont(Assets::Instance().GetPixelFont7());
  score2_.setPosition(sf::Vector2f {600, 35});
  score2_.setString(player2_.GetName() + L": " + toString(player2_.GetScore()));
  score2_.setCharacterSize(20);
  score2_.setFillColor(sf::Color::Blue);
  score2_.setStyle(sf::Text::Regular);
  
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
          score1_.setStyle(sf::Text::Regular);
          score2_.setStyle(sf::Text::Bold);
          player1_.Deactivate();
          player2_.Activate();
          polyline_.Clear();
          step_ = false;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        if (field_.correctPosition(coords, color)) {
          polyline_.AddPointPosition(coords, color);
          if (polyline_.IsClosed()) {
            convexes_.push_back(
              MakeConvex(polyline_, color, polyline_.GetThickness()));
            polyline_.Clear();
          }
        } else {
          polyline_.Clear();
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
          score1_.setStyle(sf::Text::Bold);
          score2_.setStyle(sf::Text::Regular);
          player1_.Activate();
          player2_.Deactivate();
          polyline_.Clear();
          step_ = true;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        if (field_.correctPosition(coords, color)) {
          polyline_.AddPointPosition(coords, color);
          if (polyline_.IsClosed()) {
            convexes_.push_back(
              MakeConvex(polyline_, color, polyline_.GetThickness()));
            polyline_.Clear();
          }
        } else {
          polyline_.Clear();
        }
      }
    }
  }
}

void Application::Draw() {
  window_.clear(sf::Color::White);
  field_.draw(&window_);
  for (const auto& convex : convexes_) {
    window_.draw(convex);
  }
  polyline_.Draw(&window_);
  indicator1_.Draw(&window_);
  indicator2_.Draw(&window_);
  window_.draw(score1_);
  window_.draw(score2_);
  window_.display();
}
