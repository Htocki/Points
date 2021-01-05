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
    : line { 
        sf::Vector2f { 10.f, 10.f },
        sf::Vector2f { 50.f, 50.f },
        sf::Color::Yellow,
        5 } 
  {}

 public:
  Line line;
};

TEST_F(LineTest, ConstructorWithParameters) {
  ASSERT_EQ(sf::Vector2f(10.f, 10.f), line.GetBeginPosition());
  ASSERT_EQ(sf::Vector2f(50.f, 50.f), line.GetEndPosition());
  ASSERT_EQ(sf::Color::Yellow, line.GetColor());
  ASSERT_EQ(5, line.GetThickness());
}

TEST_F(LineTest, DISABLED_Draw) {}

TEST_F(LineTest, SetBeginPosition) {
  line.SetBeginPosition(sf::Vector2f { 20.f, 20.f });
  ASSERT_EQ(sf::Vector2f(20.f, 20.f), line.GetBeginPosition());
}

TEST_F(LineTest, SetEndPosition) {
  line.SetEndPosition(sf::Vector2f { 200.f, 200.f });
  ASSERT_EQ(sf::Vector2f(200.f, 200.f), line.GetEndPosition());
}

TEST_F(LineTest, SetThickness) {
  line.SetThickness(3);
  ASSERT_EQ(3, line.GetThickness());
}

TEST_F(LineTest, GetBeginPositon) {
  ASSERT_EQ(sf::Vector2f(10.f, 10.f), line.GetBeginPosition());
}

TEST_F(LineTest, GetEndPosition) {
  ASSERT_EQ(sf::Vector2f(50.f, 50.f), line.GetEndPosition());
}

TEST_F(LineTest, GetColor) {
  ASSERT_EQ(sf::Color::Yellow, line.GetColor());
}

TEST_F(LineTest, GetThickness) {
  ASSERT_EQ(5, line.GetThickness());
}
