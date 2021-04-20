#include "gtest/gtest.h"

#include "Color.h"
#include "Line.h"
#include "Position.h"

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
    : line{ Position{ 10.f, 10.f },
            Position{ 50.f, 50.f },
            Color::Type::Yellow,
            5 }
  {}

public:
  Line line;
};

TEST_F(LineTest, ConstructorWithParameters)
{
  ASSERT_EQ(Position(10.f, 10.f), line.GetBegin());
  ASSERT_EQ(Position(50.f, 50.f), line.GetEnd());
  ASSERT_EQ(Color::Type::Yellow, line.GetColor());
  ASSERT_EQ(5, line.GetThickness());
}

TEST_F(LineTest, DISABLED_Draw) {}

TEST_F(LineTest, SetBeginPosition)
{
  line.SetBegin(Position{ 20.f, 20.f });
  ASSERT_EQ(Position(20.f, 20.f), line.GetBegin());
}

TEST_F(LineTest, SetEndPosition)
{
  line.SetEnd(Position{ 200.f, 200.f });
  ASSERT_EQ(Position(200.f, 200.f), line.GetEnd());
}

TEST_F(LineTest, SetThickness)
{
  line.SetThickness(3);
  ASSERT_EQ(3, line.GetThickness());
}

TEST_F(LineTest, GetBeginPositon)
{
  ASSERT_EQ(Position(10.f, 10.f), line.GetBegin());
}

TEST_F(LineTest, GetEndPosition)
{
  ASSERT_EQ(Position(50.f, 50.f), line.GetEnd());
}

TEST_F(LineTest, GetColor)
{
  ASSERT_EQ(Color::Type::Yellow, line.GetColor());
}

TEST_F(LineTest, GetThickness)
{
  ASSERT_EQ(5, line.GetThickness());
}
