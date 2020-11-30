#include <cstddef>
#include <exception>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

struct Size {
    sf::Uint32 width { 0 };
    sf::Uint32 height { 0 };
};

class Grid {
  public:
    Grid(const sf::Vector2f& position, const Size& size, uint32_t cell_size, sf::Color color) {
        for (sf::Uint32 i { 0 }; i <= size.width; ++i) {
            lines_.push_back({ 
                sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y), color), 
                sf::Vertex(sf::Vector2f(position.x + i * cell_size, position.y + size.height * cell_size), color)
            });
        }

        for (sf::Uint32 i { 0 }; i <= size.height; ++i) {
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
    Points(const sf::Vector2f& position, const Size& count, sf::Uint32 distance, sf::Uint32 radius, sf::Color color) {
        points_.resize(count.width * count.height);
        
        std::size_t k { 0 };
        for (sf::Uint32 i { 0 }; i < count.width; ++i) {
            for (sf::Uint32 j { 0 }; j < count.height; ++j) {
                points_.at(k).setPosition(position.x + i * distance - radius, position.y + j * distance - radius);
                ++k;
            }
        }

        for (auto& point : points_) { point.setRadius(radius); }

        for (auto& point : points_) { point.setPointCount(150); }

        for (auto& point : points_) { point.setFillColor(color); }
    }

    void setPointFillColor(const sf::Vector2f& position, const sf::Color& color) {
        for (auto& point : points_) {
            if (point.getGlobalBounds().contains(position)) {
                if (point.getFillColor() == sf::Color::White) {
                    point.setFillColor(color);
                }
            }
        }
    }

    bool isContainsNotFilledPoint(const sf::Vector2f& position) {
        for (auto& point : points_) {
            if (point.getGlobalBounds().contains(position) && point.getFillColor() == sf::Color::White) {
                return true;
            }
        }
        return false;
    }

    const sf::CircleShape& getPoint(const sf::Vector2f& position) {
        for (auto& point : points_) {
            if (point.getGlobalBounds().contains(position)) {
                return point;
            }
        }
        throw std::logic_error { "Point not found." };
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
    Player(const sf::String& name, const sf::Color& color, bool active)
        : name_ { name }
        , color_ { color }
        , active_ { active }
    {}

    void activate() { active_ = true; }
    void deactivate() { active_ = false; }
    bool isActive() const { return active_; }

    const sf::Color& getColor() const { return color_; }
    const sf::String& getName() const { return name_; }

  private:
    sf::String name_;
    sf::Color color_;
    bool active_;
};

class Assets {
  public:
    static const Assets& instance() {
        static Assets assets;
        return assets;
    }

    const sf::Font& getSansationFont() const { return m_sansation_font; };

  private:
    sf::Font m_sansation_font;

    Assets() {
        if (!m_sansation_font.loadFromFile("media/fonts/Sansation.ttf")) {
            throw std::invalid_argument { "File \"media/fonts/Sansation.ttf\" not found." };
        }
    }

    Assets(const Assets&) = delete;
    Assets &operator=(const Assets&) = delete;
};

class Label {
  public:
    Label(
        const sf::Vector2f& position, const sf::String& string, const sf::Font& font,
        const sf::Color& color, unsigned int character_size, sf::Uint32 style) 
    {
        text_.setPosition(position);
        text_.setString(string);
        text_.setFont(font);
        text_.setFillColor(color);
        text_.setCharacterSize(character_size);
        text_.setStyle(style);
    }

    void draw(sf::RenderWindow* window) {
        window->draw(text_);
    }

  private:
    sf::Text text_;
};

int main() {
    try {
        sf::RenderWindow window(sf::VideoMode(800, 600), "POINTS");
        window.setFramerateLimit(70);

        Grid grid { sf::Vector2f { 150, 50 }, Size { 20, 20 }, 25, sf::Color::Black };
        Points points { sf::Vector2f { 150, 50 }, Size { 21, 21 }, 25, 4, sf::Color::White };
    
        Player player1 { "first", sf::Color::Red, true };
        Player player2 { "second", sf::Color::Blue, false };

        sf::CircleShape focus;
        focus.setRadius(6);
        focus.setOutlineThickness(2);

        while (window.isOpen()) {
            sf::Event event;    
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) { window.close(); }
                
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f coords { window.mapPixelToCoords(sf::Mouse::getPosition(window)) };

                        if (player1.isActive() && !player2.isActive()) {
                            if (points.isContainsNotFilledPoint(coords)) {
                                points.setPointFillColor(coords, player1.getColor());
                                const auto& point { points.getPoint(coords) };
                                focus.setPosition(
                                    point.getPosition().x + point.getRadius() - focus.getRadius(),
                                    point.getPosition().y + point.getRadius() - focus.getRadius());
                                focus.setOutlineColor(player1.getColor());
                                player1.deactivate();
                                player2.activate();
                            }
                        } else {
                            if (points.isContainsNotFilledPoint(coords)) {
                                points.setPointFillColor(coords, player2.getColor());
                                const auto& point { points.getPoint(coords) };
                                focus.setPosition(
                                    point.getPosition().x + point.getRadius() - focus.getRadius(),
                                    point.getPosition().y + point.getRadius() - focus.getRadius());
                                focus.setOutlineColor(player2.getColor());
                                player1.activate();
                                player2.deactivate();
                            }
                        }
                    }
                }    
            }
            window.clear(sf::Color::White);
            grid.draw(&window);
            window.draw(focus);
            points.draw(&window);
            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
