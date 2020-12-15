#include "Application.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Assets.h"

sf::ConvexShape MakeConvex(const ClosedBoundedPolyline& polyline, const sf::Color& color) {
    sf::Color fill_color { color.r, color.g, color.b, 110 };
    sf::ConvexShape convex;
    convex.setOutlineColor(color);
    convex.setOutlineThickness(3);
    convex.setFillColor(fill_color);
    convex.setPointCount(polyline.getPointCount());
    for (unsigned int i { 0 }; i < polyline.getPointCount(); ++i) {
        convex.setPoint(i, polyline.at(i));
    }
    return convex;
}

Application::Application()
    : window_ { sf::VideoMode(800, 600), "POINTS", sf::Style::Default, sf::ContextSettings { 0, 0, 8 } }
    , grid_ { sf::Vector2f { 150, 75 }, sf::Vector2f { 20, 20 }, 25, sf::Color::Black }
    , points_ { sf::Vector2f { 150, 75 }, sf::Vector2f { 21, 21 }, 25, 4, sf::Color::White }
    , player1_ { "first", sf::Color::Red, true }
    , player2_ { "second", sf::Color::Blue, false }
    , player1_indicator_ { sf::Vector2f { 151, 40 }, sf::Vector2f { 90, 20 }, sf::Color::Red, true }
    , player2_indicator_ { sf::Vector2f { 557, 40 }, sf::Vector2f { 90, 20 }, sf::Color::Blue, false }
    , polyline_ { 37 }
    , step_ { true }
{
    window_.setFramerateLimit(70);
    focus_.setRadius(6);
    focus_.setOutlineThickness(2);

    player1_score_.SetCharacterSize(22);
    player1_score_.SetFillColor(player1_.getColor());
    player1_score_.SetFont(Assets::instance().getSansationFont());
    player1_score_.SetStyle(sf::Text::Regular);
    player1_score_.SetString("2");
    player1_score_.SetPosition(sf::Vector2f { 251, 36 });

    player2_score_.SetCharacterSize(22);
    player2_score_.SetFillColor(player2_.getColor());
    player2_score_.SetFont(Assets::instance().getSansationFont());
    player1_score_.SetStyle(sf::Text::Regular);
    player2_score_.SetString("0");
    player2_score_.SetPosition(sf::Vector2f { 532, 36 });
}

void Application::run() {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            handleEvent(event);
            draw();
        }
    }
}

void Application::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Closed) { window_.close(); }

    if (step_) {    
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };

                if (points_.isContainsNotFilledPoint(coords)) {
                    points_.setPointFillColor(coords, player1_.getColor());
                    const auto& point { points_.getPoint(coords) };
                    focus_.setPosition(
                        point.getPosition().x + point.getRadius() - focus_.getRadius(),
                        point.getPosition().y + point.getRadius() - focus_.getRadius()
                    );
                    focus_.setOutlineColor(player1_.getColor());
                    player1_indicator_.disable();
                    player2_indicator_.enable();
                    player1_.deactivate();
                    player2_.activate();
                    polyline_.clear();
                    step_ = false;
                }
            }

            if (event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };
                      
                if (points_.isPointFounded(coords, player1_.getColor())) {
                    const auto& point { points_.getPoint(coords) };
                    polyline_.addPointPosition(
                        { point.getPosition().x + point.getRadius(), point.getPosition().y + point.getRadius() },
                        player1_.getColor()
                    );
                    if (polyline_.isClosed()) {
                        convexes_.push_back(MakeConvex(polyline_, player1_.getColor()));
                        polyline_.clear();
                    }
                } else {
                    polyline_.clear();
                }
            }
        }
    } else {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };

                if (points_.isContainsNotFilledPoint(coords)) {
                    points_.setPointFillColor(coords, player2_.getColor());
                    const auto& point { points_.getPoint(coords) };
                    focus_.setPosition(
                        point.getPosition().x + point.getRadius() - focus_.getRadius(),
                        point.getPosition().y + point.getRadius() - focus_.getRadius()
                    );
                    focus_.setOutlineColor(player2_.getColor());
                    player1_indicator_.enable();
                    player2_indicator_.disable();
                    player1_.activate();
                    player2_.deactivate();
                    polyline_.clear();
                    step_ = true;
                }
            }

            if (event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };
                      
                if (points_.isPointFounded(coords, player2_.getColor())) {
                    const auto& point { points_.getPoint(coords) };
                    polyline_.addPointPosition(
                        { point.getPosition().x + point.getRadius(), point.getPosition().y + point.getRadius() },
                        player2_.getColor()
                    );
                    if (polyline_.isClosed()) {
                        convexes_.push_back(MakeConvex(polyline_, player2_.getColor()));
                        polyline_.clear();
                    }
                } else {
                    polyline_.clear();
                }
            }
        }
    } 
}

void Application::draw() {
    window_.clear(sf::Color::White);
    grid_.draw(&window_);
    window_.draw(focus_);
    points_.draw(&window_);
    for (const auto& convex : convexes_) {
        window_.draw(convex);
    }
    polyline_.draw(&window_);
    player1_indicator_.draw(&window_);
    player2_indicator_.draw(&window_);
    player1_score_.Draw(&window_);
    player2_score_.Draw(&window_);
    window_.display();
}
