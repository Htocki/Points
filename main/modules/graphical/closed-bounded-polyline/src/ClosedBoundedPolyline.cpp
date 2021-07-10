#include "ClosedBoundedPolyline.h"

ClosedBoundedPolyline::ClosedBoundedPolyline(
  unsigned int bounding_radius,
  float thickness
)
  : thickness_ {thickness}
{
  bounding_area_.setRadius(bounding_radius);
}

void ClosedBoundedPolyline::AddNode(
  const sf::Vector2f& node,
  sf::Color color
) {
  if (nodes_.size() < 1) {
    nodes_.push_back(node);
    bounding_area_.setPosition(
      node.x - bounding_area_.getRadius(),
      node.y - bounding_area_.getRadius()
    );
  } else {
    if (bounding_area_.getGlobalBounds().contains(node.x, node.y)) {
      nodes_.push_back(node);
      bounding_area_.setPosition(
        node.x - bounding_area_.getRadius(),
        node.y - bounding_area_.getRadius()
      );
      lines_.push_back(
        Line {
          sf::Vector2f {nodes_.at(nodes_.size() - 2)},
          sf::Vector2f {nodes_.at(nodes_.size() - 1)},
          color,
          thickness_
        }
      );
    } else {
      nodes_.clear();
      lines_.clear();
    }
  }
}

void ClosedBoundedPolyline::ToClear() {
  lines_.clear();
  nodes_.clear();
}

const sf::Vector2f& ClosedBoundedPolyline::At(unsigned int index) const {
  return nodes_.at(index);
}

unsigned int ClosedBoundedPolyline::BoundingRadius() const {
  return bounding_area_.getRadius();
}

bool ClosedBoundedPolyline::Closed() const {
  if (nodes_.size() > 2) {
    if (nodes_.at(0) == nodes_.at(nodes_.size() - 1)) {
      return true;
    }
  }
  return false;
}

sf::Color ClosedBoundedPolyline::Color() const {
  return lines_[0].Color();
}

bool ClosedBoundedPolyline::Empted() const {
  if (nodes_.size() > 0) {
    return false;
  }
  return true;
}

unsigned int ClosedBoundedPolyline::NodesCount() const {
  return nodes_.size();
}

float ClosedBoundedPolyline::Thickness() const {
  return thickness_;
}

void ClosedBoundedPolyline::ToDraw(sf::RenderWindow* window) const {
  for (auto& line : lines_) {
    line.ToDraw(window);
  }
}
