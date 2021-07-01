#include "gtest/gtest.h"

#include <SFML/System/Vector2.hpp>

#include "Line.h"

int
main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

class LineTest : public ::testing::Test
{
protected:
  LineTest()
    : line{ sf::Vector2f{ 10.f, 10.f },
            sf::Vector2f{ 50.f, 50.f },
            sf::Color(sf::Color::Yellow),
            5 }
  {}

public:
  Line line;
};

TEST_F(LineTest, ConstructorWithParameters)
{
  ASSERT_EQ(sf::Vector2f(10.f, 10.f), line.GetBegin());
  ASSERT_EQ(sf::Vector2f(50.f, 50.f), line.GetEnd());
  ASSERT_EQ(sf::Color(sf::Color::Yellow), line.GetColor());
  ASSERT_EQ(5, line.GetThickness());
}

TEST_F(LineTest, DISABLED_Draw) {}

TEST_F(LineTest, SetBeginPosition)
{
  line.SetBegin(sf::Vector2f{ 20.f, 20.f });
  ASSERT_EQ(sf::Vector2f(20.f, 20.f), line.GetBegin());
}

TEST_F(LineTest, SetEndPosition)
{
  line.SetEnd(sf::Vector2f{ 200.f, 200.f });
  ASSERT_EQ(sf::Vector2f(200.f, 200.f), line.GetEnd());
}

TEST_F(LineTest, SetThickness)
{
  line.SetThickness(3);
  ASSERT_EQ(3, line.GetThickness());
}

TEST_F(LineTest, GetBeginPositon)
{
  ASSERT_EQ(sf::Vector2f(10.f, 10.f), line.GetBegin());
}

TEST_F(LineTest, GetEndPosition)
{
  ASSERT_EQ(sf::Vector2f(50.f, 50.f), line.GetEnd());
}

TEST_F(LineTest, GetColor)
{
  ASSERT_EQ(sf::Color(sf::Color::Yellow), line.GetColor());
}

TEST_F(LineTest, GetThickness)
{
  ASSERT_EQ(5, line.GetThickness());
}
