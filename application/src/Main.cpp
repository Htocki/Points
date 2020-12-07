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

    bool isContainsPointWithColor(const sf::Vector2f& position, const sf::Color& color) {
        for (auto& point : points_) {
            if (point.getGlobalBounds().contains(position) && point.getFillColor() == color) {
                return true;
            }
        }
        return false;
    }

    bool isPointFounded(const sf::Vector2f& position, const sf::Color& color = sf::Color::White) {
        for (auto& point : points_) {
            if (point.getGlobalBounds().contains(position) && point.getFillColor() == color) {
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

class ClosedBoundedPolyline {
  public:
    ClosedBoundedPolyline(unsigned int bounding_radius) {
        bounding_area_.setRadius(bounding_radius);        
    }

    void addPointPosition(const sf::Vector2f& position, const sf::Color& color) {
        if (positions_.size() < 1) {
            positions_.push_back(position);
            bounding_area_.setPosition(position.x - bounding_area_.getRadius(), position.y - bounding_area_.getRadius());
        } else {
            if (bounding_area_.getGlobalBounds().contains(position)) {
                positions_.push_back(position);
                bounding_area_.setPosition(position.x - bounding_area_.getRadius(), position.y - bounding_area_.getRadius());
                lines_.push_back({ 
                    sf::Vertex(sf::Vector2f(positions_.at(positions_.size() - 2)), color),
                    sf::Vertex(sf::Vector2f(positions_.at(positions_.size() - 1)), color)
                });
            } else {
                positions_.clear();
                lines_.clear();
            } 
        }
    }

    void draw(sf::RenderWindow* window) {
        for (const auto& line : lines_) {
            window->draw(line.data(), 2, sf::Lines);
        }
    }

    bool isClosed() const { 
        if (positions_.size() > 2) {
            if (positions_.at(0) == positions_.at(positions_.size() - 1)) {
                return true;
            }
        }
        return false;
    }

    bool isEmpty() const {
        if (positions_.size() > 0) { return false; }
        return true;
    }

    unsigned int getPointCount() const { return positions_.size(); }
    
    const sf::Vector2f& at(unsigned int index) const {
        return positions_.at(index);
    }

    void clear() {
        lines_.clear();
        positions_.clear();
    }

  private:
    std::vector<std::array<sf::Vertex, 2>> lines_;
    std::vector<sf::Vector2f> positions_;
    sf::CircleShape bounding_area_;
};

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

class Application {
  public:
    Application()
       : window_ { sf::VideoMode(800, 600), "POINTS", sf::Style::Default, sf::ContextSettings { 0, 0, 8 } }
       , grid_ { sf::Vector2f { 150, 50 }, Size { 20, 20 }, 25, sf::Color::Black }
       , points_ { sf::Vector2f { 150, 50 }, Size { 21, 21 }, 25, 4, sf::Color::White }
       , player1_ { "first", sf::Color::Red, true }
       , player2_ { "second", sf::Color::Blue, false }
       , polyline_ { 37 }
    {
        window_.setFramerateLimit(70);
        focus_.setRadius(6);
        focus_.setOutlineThickness(2);
    }

    void run() {
        while (window_.isOpen()) {
            sf::Event event;
            while (window_.pollEvent(event)) {
                handleEvent(event);
                draw();
            }
        }
    }

  private:
    void handleEvent(const sf::Event& event) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
    
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };

                if (player1_.isActive() && !player2_.isActive()) {
                    if (points_.isContainsNotFilledPoint(coords)) {
                        points_.setPointFillColor(coords, player1_.getColor());
                        const auto& point { points_.getPoint(coords) };
                        focus_.setPosition(
                            point.getPosition().x + point.getRadius() - focus_.getRadius(),
                            point.getPosition().y + point.getRadius() - focus_.getRadius());
                        focus_.setOutlineColor(player1_.getColor());
                        player1_.deactivate();
                        player2_.activate();
                        polyline_.clear();
                    }
                } else {
                    if (points_.isContainsNotFilledPoint(coords)) {
                        points_.setPointFillColor(coords, player2_.getColor());
                        const auto& point { points_.getPoint(coords) };
                        focus_.setPosition(
                        point.getPosition().x + point.getRadius() - focus_.getRadius(),
                            point.getPosition().y + point.getRadius() - focus_.getRadius());
                        focus_.setOutlineColor(player2_.getColor());
                        player1_.activate();
                        player2_.deactivate();
                        polyline_.clear();
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Right) {
                sf::Vector2f coords { window_.mapPixelToCoords(sf::Mouse::getPosition(window_)) };
                      
                if (player1_.isActive() && !player2_.isActive()) {
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
                } else {
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

    void draw() {
        window_.clear(sf::Color::White);
        grid_.draw(&window_);
        window_.draw(focus_);
        points_.draw(&window_);
        for (const auto& convex : convexes_) {
            window_.draw(convex);
        }
        polyline_.draw(&window_);
        window_.display();
    }

    sf::RenderWindow window_;
    Grid grid_;
    Points points_;
    Player player1_;
    Player player2_;
    sf::CircleShape focus_;
    ClosedBoundedPolyline polyline_;
    std::vector<sf::ConvexShape> convexes_;
};

int main() {
    try {
        Application application;
        application.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
