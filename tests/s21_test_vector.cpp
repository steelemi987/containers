#include "s21_tests.h"

TEST(Vector_Constructor, Default) {
  s21::vector<int> int_temp;
  s21::vector<double> double_temp;

  EXPECT_EQ(int_temp.empty(), 1);
  EXPECT_EQ(double_temp.empty(), 1);
}

TEST(Vector_Constructor, Size) {
  s21::vector<int> int_temp(5);
  s21::vector<double> double_temp(5);
  size_t i = 5;

  EXPECT_EQ(int_temp.size(), i);
  EXPECT_EQ(int_temp.size(), i);
}

TEST(Vector_Constructor, Initializer_List) {
  s21::vector<int> int_temp = {1, 2, 3, 4, -5};
  s21::vector<double> double_temp = {1, 2.2, -3.5};
  size_t i = 5;

  EXPECT_EQ(int_temp.size(), i);
  EXPECT_EQ(int_temp.size(), i);
}

TEST(Vector_Constructor, Copy) {
  s21::vector<int> int_temp = {1, 3, 5};
  s21::vector<int> copy(int_temp);
  size_t i = 3;

  EXPECT_EQ(copy.size(), i);
}

TEST(Vector_Constructor, Move) {
  s21::vector<int> int_temp = {1, 3, 5};
  s21::vector<int> move(std::move(int_temp));
  size_t i = 3;

  EXPECT_EQ(move.size(), i);
  EXPECT_EQ(int_temp.empty(), 1);
}

TEST(Vector_Constructor, Operator_Eq) {
  s21::vector<int> int_temp = {1, 3, 5};
  s21::vector<int> move = int_temp;
  size_t i = 3;

  EXPECT_EQ(move.size(), i);
}

TEST(Vector_Element_Access, At) {
  s21::vector<int> int_temp = {1, 3, 5};

  EXPECT_EQ(int_temp.at(2), 5);
}

TEST(Vector_Element_Access, At_Wrong) {
  s21::vector<int> int_temp = {1, 3, 5};

  EXPECT_THROW(int_temp.at(5), std::out_of_range);
}

TEST(Vector_Element_Access, Operator_At) {
  s21::vector<int> int_temp = {1, 3, 5};

  EXPECT_EQ(int_temp[2], 5);
}

TEST(Vector_Element_Access, Operator_At_Wrong) {
  s21::vector<int> int_temp = {1, 3, 5};

  EXPECT_THROW(int_temp[5], std::out_of_range);
}

TEST(Vector_Element_Access, Front) {
  s21::vector<int> int_temp = {1, 3, 5};

  EXPECT_EQ(int_temp.front(), 1);
}

TEST(Vector_Element_Access, Front_Wrong) {
  s21::vector<int> int_temp;

  EXPECT_THROW(int_temp.front(), std::out_of_range);
}

TEST(Vector_Element_Access, Back) {
  s21::vector<int> int_temp = {1, 3, 5};

  EXPECT_EQ(int_temp.back(), 5);
}

TEST(Vector_Element_Access, Back_Wrong) {
  s21::vector<int> int_temp;

  EXPECT_THROW(int_temp.back(), std::out_of_range);
}

TEST(Vector_Element_Access, Data) {
  s21::vector<int> int_temp = {1, 2, 3};
  int* value = int_temp.data();

  EXPECT_EQ(value[0], 1);
}

// iterators

TEST(Vector_Iterators, Begin) {
  s21::vector<int> int_temp = {1, 2, 3};
  s21::vector<int>::iterator it = int_temp.begin();

  EXPECT_EQ(*it, 1);
}

TEST(Vector_Iterators, End) {
  s21::vector<int> int_temp = {1, 2, 3};

  EXPECT_EQ(int_temp.end(), int_temp.begin() + 3);
}

// capacity

TEST(Vector_Capacity, Empty) {
  s21::vector<int> int_temp;
  s21::vector<int> int_temp2(2);

  EXPECT_EQ(int_temp.empty(), 1);
  EXPECT_EQ(int_temp2.empty(), 0);
}

TEST(Vector_Capacity, Size) {
  s21::vector<int> int_temp;
  s21::vector<int> int_temp2(2);
  size_t i1 = 0, i2 = 2;

  EXPECT_EQ(int_temp.size(), i1);
  EXPECT_EQ(int_temp2.size(), i2);
}

TEST(Vector_Capacity, Max_Size) {
  s21::vector<int> int_temp = {1, 2, 3, 4, 5};

  EXPECT_EQ(int_temp.max_size() >= int_temp.size(), 1);
}

TEST(Vector_Capacity, Reserve) {
  s21::vector<int> int_temp(3);
  int_temp.reserve(7);
  size_t i = 7;

  EXPECT_EQ(int_temp.capacity(), i);
}

TEST(Vector_Capacity, Reserve_MaxSize) {
  s21::vector<int> int_temp(3);

  EXPECT_THROW(int_temp.reserve(int_temp.max_size() + 1), std::out_of_range);
}

TEST(Vector_Capacity, Capacity) {
  s21::vector<int> int_temp(3);
  size_t i = 3;

  EXPECT_EQ(int_temp.capacity(), i);
}

TEST(Vector_Capacity, Shrink) {
  s21::vector<int> int_temp = {1, 2, 3};
  size_t i = 3;
  EXPECT_EQ(int_temp.capacity(), i);

  int_temp.reserve(7);
  size_t i1 = 7;
  EXPECT_EQ(int_temp.capacity(), i1);

  int_temp.shrink_to_fit();
  size_t i2 = 3;
  EXPECT_EQ(int_temp.capacity(), i2);
}

// modifiers

TEST(Vector_Modifiers, Clear) {
  s21::vector<int> int_temp(3);

  EXPECT_EQ(int_temp.empty(), 0);

  int_temp.clear();

  EXPECT_EQ(int_temp.empty(), 1);
}

TEST(Vector_Modifiers, Insert) {
  s21::vector<int> int_temp = {1, 2, 3};
  int_temp.insert(int_temp.begin(), 7);
  size_t i = 4;
  EXPECT_EQ(int_temp[0], 7);
  EXPECT_EQ(int_temp.size(), i);
}

TEST(Vector_Modifiers, Erase) {
  s21::vector<int> int_temp = {1, 2, 3};
  int_temp.erase(int_temp.begin());
  size_t i = 2;
  EXPECT_EQ(int_temp[0], 2);
  EXPECT_EQ(int_temp.size(), i);
}

TEST(Vector_Modifiers, Push_Back) {
  s21::vector<int> int_temp = {1, 2, 3};
  int_temp.push_back(7);
  size_t i = 4;
  EXPECT_EQ(int_temp[3], 7);
  EXPECT_EQ(int_temp.size(), i);
}

TEST(Vector_Modifiers, Pop_Back) {
  s21::vector<int> int_temp = {1, 2, 3};

  EXPECT_EQ(int_temp[2], 3);

  int_temp.pop_back();

  EXPECT_ANY_THROW(int_temp[2]);
}

TEST(Vector_Modifiers, Swap) {
  s21::vector<int> int_temp = {1, 2, 3};
  s21::vector<int> int_temp2 = {4, 5, 6, 7};
  int_temp.swap(int_temp2);
  size_t i1 = 4;
  EXPECT_EQ(int_temp[0], 4);
  EXPECT_EQ(int_temp.size(), i1);
  size_t i2 = 3;
  EXPECT_EQ(int_temp2[0], 1);
  EXPECT_EQ(int_temp2.size(), i2);
}

TEST(Vector_Insert_Many, Insert_Many) {
  s21::vector<int> int_temp = {1, 2, 6, 7, 8};
  auto it = int_temp.insert_many(int_temp.begin() + 2, 3, 4, 5);
  size_t i = 8;
  EXPECT_EQ(*it == 6, 1);
  EXPECT_EQ(int_temp.size(), i);
}

TEST(Vector_Insert_Many, Insert_Many_Back) {
  s21::vector<int> int_temp = {1, 2, 6, 7, 8};
  int_temp.insert_many_back(3, 4, 5);

  size_t i = 8;
  EXPECT_EQ(int_temp.size(), i);

  EXPECT_EQ(int_temp[7] == 5, 1);
  EXPECT_EQ(int_temp[6] == 4, 1);
  EXPECT_EQ(int_temp[5] == 3, 1);
}
