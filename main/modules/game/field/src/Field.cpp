#include "Field.h"

#include <algorithm>

Field::Field(
  sf::Vector2f position,
  sf::Vector2f size,
  float cell_size,
  sf::Color color,
  float nodes_radius
) 
  : position_(position)
  , size_(size)
  , csize_(cell_size)
  , color_(color)
{
  nodes_.resize(size.x * size.y);

  size_t k {0};
  for (size_t i {0}; i < size.x; ++i) {
    for (size_t j {0}; j < size.y; ++j) {
      nodes_.at(k).setPosition(
        position.x + i*cell_size - nodes_radius,
        position.y + j*cell_size - nodes_radius);
      ++k;
    }
  }

  for (auto& node : nodes_) {
    node.setRadius(nodes_radius);
    node.setPointCount(150);
    node.setFillColor(color);
  }

  last_.setRadius(7);
  last_.setOutlineThickness(1);
}

sf::Vector2f Field::getPosition() const {
  return position_;
}

sf::Vector2f Field::getSize() const {
  return size_ * csize_;
}

float Field::getCellSize() const {
  return csize_;
}

float Field::getNodesRadius() const {
  return nodes_[0].getRadius();
}

bool Field::setNodeColor(sf::Vector2f position, sf::Color color) {
  for (auto& node : nodes_) {
    if (node.getGlobalBounds().contains(position) &&
      node.getFillColor() == color_) {
      node.setFillColor(color);
      last_.setPosition(
        node.getPosition().x + getNodesRadius() - last_.getRadius(),
        node.getPosition().y + getNodesRadius() - last_.getRadius()
      );
      last_.setOutlineColor(color);
      return true;
    }
  }
  return false;
}

bool Field::correctPosition(sf::Vector2f& position, sf::Color color) const {
  for (auto& node : nodes_) {
    if (node.getGlobalBounds().contains(position)
      && node.getFillColor() == color) {
      position.x = node.getPosition().x + node.getRadius();
      position.y = node.getPosition().y + node.getRadius();
      return true;
    }
  }
  return false;
}

void Field::draw(sf::RenderWindow* window) const
{
  // Отрисовка сетки
  for (size_t i {0}; i <= size_.x; ++i) {
    sf::Vertex line[] = {
      sf::Vertex(
        sf::Vector2f(position_.x + i*csize_, position_.y)),
      sf::Vertex(
        sf::Vector2f(position_.x + i*csize_, position_.y + size_.y*csize_))
    };
    line[0].color = color_;
    line[1].color = color_;
    window->draw(line, 2, sf::Lines);
  }

  for (size_t i {0}; i <= size_.y; ++i) {
    sf::Vertex line[] = {
      sf::Vertex(
        sf::Vector2f(position_.x, position_.y + i*csize_)),
      sf::Vertex(
        sf::Vector2f(position_.x + size_.x*csize_, position_.y + i*csize_))
    };
    line[0].color = color_;
    line[1].color = color_;
    window->draw(line, 2, sf::Lines);
  }

  // Отрисовка последнего отмеченного узла
  window->draw(last_);
  
  // Отрисовка узлов
  for (const auto& node : nodes_) {
    if (node.getFillColor() != color_) {
      window->draw(node);
    }
  }
}