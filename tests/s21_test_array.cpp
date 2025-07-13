#include "s21_tests.h"

// functions

TEST(Array_Constructor, Default_Empty) {
  s21::array<int, 0> temp;

  EXPECT_EQ(temp.empty(), 1);
}

TEST(Array_Constructor, Default_Not_Empty) {
  s21::array<double, 5> temp;

  EXPECT_EQ(temp.empty(), 0);
}

TEST(Array_Constructor, Initializer_List) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.size(), 3);
}

TEST(Array_Constructor, Copy) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> copy(temp);

  EXPECT_EQ(copy.size(), 3);
}

TEST(Array_Constructor, Move) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> move(std::move(temp));

  EXPECT_EQ(temp.empty(), 1);
  EXPECT_EQ(move.size(), 3);
}

TEST(Array_Constructor, Operator_Eq) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> move;
  move = std::move(temp);

  EXPECT_EQ(move.size(), 3);
}

// element access

TEST(Array_Element_Access, At) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.at(1), 2);
}

TEST(Array_Element_Access, At_OutOfRange) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_THROW(temp.at(7), std::out_of_range);
}

TEST(Array_Element_Access, Operator_At) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp[1], 2);
}

TEST(Array_Element_Access, Front) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.front(), 1);
}

TEST(Array_Element_Access, Back) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.back(), 3);
}

TEST(Array_Element_Access, Data) {
  s21::array<int, 3> temp = {1, 2, 3};
  int* value = temp.data();

  EXPECT_EQ(value[0], 1);
}

TEST(Array_Iterators, Begin) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(*(temp.begin()), 1);
}

TEST(Array_Iterators, End) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.end(), temp.begin() + 3);
}

TEST(Array_Capacity, Empty) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.empty(), 0);
}

TEST(Array_Capacity, Size) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.size(), 3);
}

TEST(Array_Capacity, Max_Size) {
  s21::array<int, 3> temp = {1, 2, 3};

  EXPECT_EQ(temp.max_size(), 3);
}

TEST(Array_Modifiers, Swap) {
  s21::array<int, 3> temp = {1, 2, 3};
  s21::array<int, 3> temp2 = {4, 5, 6};
  temp.swap(temp2);

  EXPECT_EQ(temp.front(), 4);
  EXPECT_EQ(temp.back(), 6);
  EXPECT_EQ(temp2.front(), 1);
  EXPECT_EQ(temp2.back(), 3);
}

TEST(Array_Modifiers, Fill) {
  s21::array<int, 3> temp = {1, 2, 3};
  temp.fill(5);

  EXPECT_EQ(temp.front(), 5);
  EXPECT_EQ(temp.back(), 5);
}
