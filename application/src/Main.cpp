#include <cstddef>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using Position = sf::Vector2f;

struct Size {
    std::uint32_t width { 0 };
    std::uint32_t height { 0 };
};

class Grid {
  public:
    Grid(const Position& position, const Size& size, uint32_t cell_size, sf::Color color) {
        for (std::uint32_t i { 0 }; i <= size.width; ++i) {
            lines_.push_back({ 
                sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y), color), 
                sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y + size.height * cell_size), color)
            });
        }

        for (std::uint32_t i { 0 }; i <= size.height; ++i) {
            lines_.push_back({
                sf::Vertex(sf::Vector2f(position.x, position.y + i * cell_size), color),
                sf::Vertex(sf::Vector2f(position.x + size.width * cell_size, position.y + i * cell_size), color)
            });
        }
    }

    void draw(sf::RenderWindow* window) {
        for (const auto& line : lines_) {
            window->draw(line.data(), 2, sf::Lines);
        }
    }

  private:
    std::vector<std::array<sf::Vertex, 2>> lines_;
};

class Points {
  public:
    Points(const Position& position, const Size& count, std::uint32_t distance, std::uint32_t radius, sf::Color color) {
        points_.resize(count.width * count.height);
        
        std::size_t k { 0 };
        for (std::uint32_t i { 0 }; i < count.width; ++i) {
            for (std::uint32_t j { 0 }; j < count.height; ++j) {
                points_.at(k).setPosition(position.x + i * distance - radius, position.y + j * distance - radius);
                ++k;
            }
        }

        for (auto& point : points_) { point.setRadius(radius); }

        for (auto& point : points_) { point.setPointCount(150); }

        for (auto& point : points_) { point.setFillColor(color); }
    }

    void handleEvent(const sf::RenderWindow& window, const sf::Event& event, const sf::Color color) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i pixel { sf::Mouse::getPosition(window) };
                sf::Vector2f coords { window.mapPixelToCoords(pixel) };
                for (auto& point : points_) {
                    if (point.getGlobalBounds().contains(coords)) {
                        point.setFillColor(color);
                    }
                }
            }
        }
    }

    void draw(sf::RenderWindow* window) {
        for (const auto& point : points_) {
            if (point.getFillColor() != sf::Color::White) {
                window->draw(point);
            }
        }
    }

  private:
    std::vector<sf::CircleShape> points_;
};

class Player {
  public:
    Player(const sf::String& name, const sf::Color& color)
        : name_ { name }
        , color_ { color }
    {}

    const sf::Color& getColor() const { return color_; }
    const sf::String& getName() const { return name_; }

  private:
    sf::String name_;
    sf::Color color_;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Points");

    Grid grid { Position { 150, 50 }, Size { 20, 20 }, 25, sf::Color::Black };
    Points points { Position { 150, 50 }, Size { 21, 21 }, 25, 4, sf::Color::White };
    Player player1 { "Player1", sf::Color::Red };
    Player player2 { "Player2", sf::Color::Blue };
    
    while (window.isOpen()) {
        sf::Event event;    
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            points.handleEvent(window, event, sf::Color::Red);    
        }
        window.clear(sf::Color::White);
        grid.draw(&window);
        points.draw(&window);
        window.display();
    }
    return 0;
}