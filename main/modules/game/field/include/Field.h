#pragma once

#include <vector>

#include <SFML/Config.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

struct Bounds {
  float left {0};
  float right {0};
  float top {0};
  float button {0};
};

class Field {
 public:
  Field(
    sf::Vector2f position,
    sf::Vector2f size,
    float cell_size,
    sf::Color color,
    float nodes_radius
  );

  sf::Vector2f  getPosition() const;
  sf::Vector2f  getSize() const;
  float         getCellSize() const;
  sf::Color     getColor() const;
  float         getNodesRadius() const;

  // Изменяет цвет узла на указанный, если заданная позиция находится в его
  // радиусе.
  bool setNodeColor(sf::Vector2f position, sf::Color color);
  // Изменяет позицию указателя мыши на экране на центр узла, в радиусе
  // которого она находится в радиусе какого-то из узлов, изменяет на центр этого узла.
  bool correctPosition(sf::Vector2f& position, sf::Color color) const;

  void draw(sf::RenderWindow* window) const;

 private:
  sf::Vector2f position_;               // Границы заполнения
  sf::Vector2f size_;                   // Размеры (в клетках)
  float csize_;                         // Размер клетки
  sf::Color color_;                     // Цвет
  std::vector<sf::CircleShape> nodes_;  // Узлы
  sf::CircleShape last_;                // Последний добавленный узел
};
