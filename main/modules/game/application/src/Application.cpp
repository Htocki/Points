#include "Application.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Assets.h"

sf::ConvexShape MakeConvex(const ClosedBoundedPolyline& polyline, const Color& color, float thickness) {
  sf::ConvexShape convex;
  convex.setOutlineColor({ color.R(), color.G(), color.B(), color.A() });
  convex.setOutlineThickness(thickness);
  convex.setFillColor({ color.R(), color.G(), color.B(), 110 });
  convex.setPointCount(polyline.GetPointCount());
  for (unsigned int i { 0 }; i < polyline.GetPointCount(); ++i) {
    convex.setPoint(i, { polyline.At(i).X(), polyline.At(i).Y() });
  }
  return convex;
}

Application::Application()
  : window_ { sf::VideoMode(800, 600), "POINTS", sf::Style::Default, sf::ContextSettings { 0, 0, 8 } }
  , grid_ { { 150, 75 }, { 20, 20 }, 25, Color::Type::Black, 4 }
  , points_ { sf::Vector2f { 150, 75 }, sf::Vector2f { 21, 21 }, 25, 5, sf::Color::White }
  , player1_ { "first", Color::Type::Red, true }
  , player2_ { "second", Color::Type::Blue, false }
  , player1_indicator_ { sf::Vector2f { 151, 40 }, sf::Vector2f { 90, 20 }, sf::Color::Red, true }
  , player2_indicator_ { sf::Vector2f { 557, 40 }, sf::Vector2f { 90, 20 }, sf::Color::Blue, false }
  , polyline_ { 37, 4 }
  , step_ { true }
{
  window_.setFramerateLimit(70);
  focus_.setRadius(7);
  focus_.setOutlineThickness(1);
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
  if (event.type == sf::Event::Closed) { window_.close(); }

  if (step_) {    
    if (event.type == sf::Event::MouseButtonPressed) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };
        const auto color { player1_.GetColor() };
        if (points_.IsContainsNotFilledPoint(coords)) {
          points_.SetPointFillColor(coords, { color.R(), color.G(), color.B(), color.A() });
          const auto& point { points_.GetPoint(coords) };
          focus_.setPosition(
            point.getPosition().x + point.getRadius() - focus_.getRadius(),
            point.getPosition().y + point.getRadius() - focus_.getRadius()
          );
          focus_.setOutlineColor({ color.R(), color.G(), color.B(), color.A() });
          player1_indicator_.Disable();
          player2_indicator_.Enable();
          player1_.Deactivate();
          player2_.Activate();
          polyline_.Clear();
          step_ = false;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };
        const auto color { player1_.GetColor() };          
        if (points_.IsPointFounded(coords, { color.R(), color.G(), color.B(), color.A() })) {
          const auto& point { points_.GetPoint(coords) };
          polyline_.AddPointPosition(
            { point.getPosition().x + point.getRadius(), point.getPosition().y + point.getRadius() },
            player1_.GetColor()
          );
          if (polyline_.IsClosed()) {
            convexes_.push_back(
              MakeConvex(
                polyline_,
                player1_.GetColor(),
                polyline_.GetThickness()
              )
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
      if (event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };
        const auto color { player2_.GetColor() };
        if (points_.IsContainsNotFilledPoint(coords)) {
          points_.SetPointFillColor(coords, { color.R(), color.G(), color.B(), color.A() });
          const auto& point { points_.GetPoint(coords) };
          focus_.setPosition(
            point.getPosition().x + point.getRadius() - focus_.getRadius(),
            point.getPosition().y + point.getRadius() - focus_.getRadius()
          );
          focus_.setOutlineColor({ color.R(), color.G(), color.B(), color.A() });
          player1_indicator_.Enable();
          player2_indicator_.Disable();
          player1_.Activate();
          player2_.Deactivate();
          polyline_.Clear();
          step_ = true;
        }
      }

      if (event.mouseButton.button == sf::Mouse::Right) {
        sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };
        const auto color { player2_.GetColor() };          
        if (points_.IsPointFounded(coords, { color.R(), color.G(), color.B(), color.A() })) {
          const auto& point { points_.GetPoint(coords) };
          polyline_.AddPointPosition(
            { point.getPosition().x + point.getRadius(), point.getPosition().y + point.getRadius() },
            player2_.GetColor()
          );
          if (polyline_.IsClosed()) {
            convexes_.push_back(MakeConvex(polyline_, player2_.GetColor(), polyline_.GetThickness()));
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
  grid_.Draw(&window_);
  window_.draw(focus_);
  points_.Draw(&window_);
  for (const auto& convex : convexes_) {
    window_.draw(convex);
  }
  polyline_.Draw(&window_);
  player1_indicator_.Draw(&window_);
  player2_indicator_.Draw(&window_);

  window_.display();
}
