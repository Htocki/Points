#include "BoundedPolygon.h"

#include <SFML/Graphics/ConvexShape.hpp>

BoundedPolygon::BoundedPolygon(unsigned int bounding_radius, float thickness)
  : ClosedBoundedPolyline {bounding_radius, thickness}
{}

void BoundedPolygon::ToDraw(sf::RenderWindow* window) const {
  ClosedBoundedPolyline::ToDraw(window);
  if (Closed()) {
    sf::ConvexShape convexity;
    convexity.setOutlineColor(Color());
    convexity.setOutlineThickness(1);
    convexity.setFillColor(
      sf::Color{Color().r, Color().g, Color().b, sf::Uint8{125}}
    );
    convexity.setPointCount(NodesCount());
    for (unsigned int i {0}; i < NodesCount(); ++i) {
      convexity.setPoint(i, sf::Vector2f{At(i).x, At(i).y});
    }
    window->draw(convexity);
  }
}