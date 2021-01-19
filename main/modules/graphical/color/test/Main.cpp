#include "gtest/gtest.h"

#include "Color.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ColorTest, Color) {
  Color color;
  ASSERT_EQ(color.R(), 0);
  ASSERT_EQ(color.G(), 0);
  ASSERT_EQ(color.B(), 0);
  ASSERT_EQ(color.A(), 255);
}

TEST(ColorTest, Color_Type) {
  Color color(Color::Type::Red);
  ASSERT_EQ(color.R(), 255);
  ASSERT_EQ(color.G(), 0);
  ASSERT_EQ(color.B(), 0);
  ASSERT_EQ(color.A(), 255);
}

TEST(ColorTest, Color_TypeTransparency) {
  Color color(Color::Type::Blue, Color::Transparency::Invisible);
  ASSERT_EQ(color.R(), 0);
  ASSERT_EQ(color.G(), 0);
  ASSERT_EQ(color.B(), 255);
  ASSERT_EQ(color.A(), 0);
}

TEST(ColorTest, Color_UInt8UInt8UInt8UInt8) {
  Color color(122, 10, 14, 222);
  ASSERT_EQ(color.R(), 122);
  ASSERT_EQ(color.G(), 10);
  ASSERT_EQ(color.B(), 14);
  ASSERT_EQ(color.A(), 222);
}

TEST(ColorTest, SetA_UInt8) {
  Color color(122, 10, 14, 222);
  color.SetA(111);
  ASSERT_EQ(color.R(), 122);
  ASSERT_EQ(color.G(), 10);
  ASSERT_EQ(color.B(), 14);
  ASSERT_EQ(color.A(), 111);
}

TEST(ColorTest, SetB_UInt8) {
  Color color(122, 10, 14, 222);
  color.SetB(100);
  ASSERT_EQ(color.R(), 122);
  ASSERT_EQ(color.G(), 10);
  ASSERT_EQ(color.B(), 100);
  ASSERT_EQ(color.A(), 222);
}

TEST(ColorTest, SetG_UInt8) {
  Color color(122, 10, 14, 222);
  color.SetG(232);
  ASSERT_EQ(color.R(), 122);
  ASSERT_EQ(color.G(), 232);
  ASSERT_EQ(color.B(), 14);
  ASSERT_EQ(color.A(), 222);
}

TEST(ColorTest, SetR_UInt8) {
  Color color(122, 10, 14, 222);
  color.SetR(8);
  ASSERT_EQ(color.R(), 8);
  ASSERT_EQ(color.G(), 10);
  ASSERT_EQ(color.B(), 14);
  ASSERT_EQ(color.A(), 222);
}

TEST(ColorTest, SetType_type) {
  Color color(122, 10, 14, 222);
  color.SetType(Color::Type::Red);
  ASSERT_EQ(color.R(), 255);
  ASSERT_EQ(color.G(), 0);
  ASSERT_EQ(color.B(), 0);
  ASSERT_EQ(color.A(), 222);
}

TEST(ColorTest, SetType_UInt8UInt8UInt8) {
  Color color(122, 10, 14, 222);
  color.SetType(3, 3, 3);
  ASSERT_EQ(color.R(), 3);
  ASSERT_EQ(color.G(), 3);
  ASSERT_EQ(color.B(), 3);
  ASSERT_EQ(color.A(), 222);
}

TEST(ColorTest, SetTransparency_Transparency) {
  Color color(122, 10, 14, 222);
  color.SetTransparency(Color::Transparency::Visible);
  ASSERT_EQ(color.R(), 122);
  ASSERT_EQ(color.G(), 10);
  ASSERT_EQ(color.B(), 14);
  ASSERT_EQ(color.A(), 255);
}

TEST(COlorTest, SetTransparency_UInt8) {
  Color color(122, 10, 14, 222);
  color.SetTransparency(128);
  ASSERT_EQ(color.R(), 122);
  ASSERT_EQ(color.G(), 10);
  ASSERT_EQ(color.B(), 14);
  ASSERT_EQ(color.A(), 128);
}
