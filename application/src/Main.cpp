#include <cstddef>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using Position = sf::Vector2f;

struct Size {
    std::uint32_t width { 0 };
    std::uint32_t height { 0 };
};

class Grid {
  public:
    Grid(const Position& position, const Size& size, uint32_t cell_size)
        : position_ { position }
        , size_ { size }
        , cell_size_ { cell_size }
    {
        for (std::uint32_t i { 0 }; i <= size.width; ++i)
            lines_.push_back({ 
                sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y)), 
                sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y + size.height * cell_size))
            });
        for (std::uint32_t i { 0 }; i <= size.height; ++i)
            lines_.push_back({
                sf::Vertex(sf::Vector2f(position.x,                          position.y + i * cell_size)),
                sf::Vertex(sf::Vector2f(position.x + size.width * cell_size, position.y + i * cell_size))
            });
    }

    void draw(sf::RenderWindow* window) {
        for (const auto& line : lines_) {
            window->draw(line.data(), 2, sf::Lines);
        }
    }

    const Position& getPosition() { return position_; }
    const Size& getSize() { return size_; }
    const std::uint32_t getCellSize() { return cell_size_; }

  private:
    Position position_;
    Size size_;
    std::uint32_t cell_size_;
    std::vector<std::array<sf::Vertex, 2>> lines_;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Points");

    Grid grid { Position { 150, 50 }, Size { 20, 20 }, 20 };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        grid.draw(&window);
        window.display();
    }
    return 0;
}