#include "Application.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Assets.h"

sf::ConvexShape
MakeConvex(const ClosedBoundedPolyline& polyline,
           const Color& color,
           float thickness)
{
  sf::ConvexShape convex;
  convex.setOutlineColor({ color.R(), color.G(), color.B(), color.A() });
  convex.setOutlineThickness(thickness);
  convex.setFillColor({ color.R(), color.G(), color.B(), 110 });
  convex.setPointCount(polyline.GetPointCount());
  for (unsigned int i{ 0 }; i < polyline.GetPointCount(); ++i) {
    convex.setPoint(i, { polyline.At(i).X(), polyline.At(i).Y() });
  }
  return convex;
}

Application::Application()
  : window_ { sf::VideoMode(800, 600),
             "POINTS",
             sf::Style::Default,
             sf::ContextSettings{ 0, 0, 8 } }
  , field_(
      sf::Vector2f(100.f, 90.f),
      sf::Vector2f(30.f, 20.f),
      20,
      sf::Color::Black,
      5)
  , player1_{ "first", Color::Type::Red, true }
  , player2_{ "second", Color::Type::Blue, false }
  , player1_indicator_{ sf::Vector2f{ 151, 40 },
                        sf::Vector2f{ 90, 20 },
                        sf::Color::Red,
                        true }
  , player2_indicator_{ sf::Vector2f{ 557, 40 },
                        sf::Vector2f{ 90, 20 },
                        sf::Color::Blue,
                        false }
  , polyline_{ 37, 4 }
  , step_{ true }
{
  window_.setFramerateLimit(70);
}

void
Application::Run()
{
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      HandleEvent(event);
      Draw();
    }
  }
}

void
Application::HandleEvent(const sf::Event& event)
{
  if (event.type == sf::Event::Closed) {
    window_.close();
  }

  sf::Vector2f coords{ window_.mapPixelToCoords(
    sf::Mouse::getPosition(window_))
  };

  if (step_) {
    if (event.type == sf::Event::MouseButtonPressed) {
      const auto col{ player1_.GetColor() };
      sf::Color color {col.R(), col.G(), col.B(), col.A()};
      
      if (event.mouseButton.button == sf::Mouse::Left) {
        if (field_.setNodeColor(coords, color)) {
          player1_indicator_.Disable();
          player2_indicator_.Enable();
          player1_.Deactivate();
          player2_.Activate();
          polyline_.Clear();
          step_ = false;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        if (field_.correctPosition(coords, color)) {
          polyline_.AddPointPosition(
            {coords.x, coords.y}, 
            {color.r, color.g, color.b, color.a}
          );
          if (polyline_.IsClosed()) {
            convexes_.push_back(MakeConvex(
              polyline_,
              {color.r, color.g, color.b, color.a},
              polyline_.GetThickness())
            );
            polyline_.Clear();
          }
        } else {
          polyline_.Clear();
        }
      }
    }
  } else {
    if (event.type == sf::Event::MouseButtonPressed) {
      const auto col{ player2_.GetColor() };
      sf::Color color {col.R(), col.G(), col.B(), col.A()};
      
      if (event.mouseButton.button == sf::Mouse::Left) {
        if (field_.setNodeColor(coords, color)) {
          player1_indicator_.Enable();
          player2_indicator_.Disable();
          player1_.Activate();
          player2_.Deactivate();
          polyline_.Clear();
          step_ = true;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        if (field_.correctPosition(coords, color)) {
          polyline_.AddPointPosition(
            {coords.x, coords.y}, 
            {color.r, color.g, color.b, color.a}
          );
          if (polyline_.IsClosed()) {
            convexes_.push_back(MakeConvex(
              polyline_,
              {color.r, color.g, color.b, color.a},
              polyline_.GetThickness())
            );
            polyline_.Clear();
          }
        } else {
          polyline_.Clear();
        }
      }
    }
  }
}

void
Application::Draw()
{
  window_.clear(sf::Color::White);
  field_.draw(&window_);
  for (const auto& convex : convexes_) {
    window_.draw(convex);
  }
  polyline_.Draw(&window_);
  player1_indicator_.Draw(&window_);
  player2_indicator_.Draw(&window_);

  window_.display();
}
