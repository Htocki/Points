#include "gtest/gtest.h"

#include <SFML/System/Vector2.hpp>

#include "Line.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

class LineTest : public ::testing::Test {
protected:
  LineTest()
    : line {sf::Vector2f {10.f, 10.f}, sf::Vector2f {50.f, 50.f}, sf::Color {sf::Color::Yellow}, 5}
  {}

public:
  Line line;
};

TEST_F(LineTest, ConstructorWithParameters) {
  ASSERT_EQ(sf::Vector2f(10.f, 10.f), line.Begin());
  ASSERT_EQ(sf::Vector2f(50.f, 50.f), line.End());
  ASSERT_EQ(sf::Color {sf::Color::Yellow}, line.Color());
  ASSERT_EQ(5, line.Thickness());
}

TEST_F(LineTest, DISABLED_Draw) {}

TEST_F(LineTest, SetBeginPosition) {
  line.ToChangeBegin(sf::Vector2f {20.f, 20.f});
  ASSERT_EQ(sf::Vector2f(20.f, 20.f), line.Begin());
}

TEST_F(LineTest, SetEndPosition) {
  line.ToChangeEnd(sf::Vector2f {200.f, 200.f});
  ASSERT_EQ(sf::Vector2f(200.f, 200.f), line.End());
}

TEST_F(LineTest, SetThickness) {
  line.ToChangeThickness(3);
  ASSERT_EQ(3, line.Thickness());
}

TEST_F(LineTest, GetBeginPositon) {
  ASSERT_EQ(sf::Vector2f(10.f, 10.f), line.Begin());
}

TEST_F(LineTest, GetEndPosition) {
  ASSERT_EQ(sf::Vector2f(50.f, 50.f), line.End());
}

TEST_F(LineTest, GetColor) {
  ASSERT_EQ(sf::Color {sf::Color::Yellow}, line.Color());
}

TEST_F(LineTest, GetThickness) {
  ASSERT_EQ(5, line.Thickness());
}
