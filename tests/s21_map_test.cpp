#include <type_traits>

#include "s21_tests.h"
TEST(map_constructor, no_arg) {
  s21::map<int, int> _map;
  EXPECT_EQ(_map.empty(), 1);
}

TEST(map_constructor, initializer_list) {
  s21::map<int, int> _map({std::pair<int, int>{11, 2}, {99, 0}});
  EXPECT_EQ(_map.empty(), 0);
}

TEST(map_constructor, copy) {
  s21::map<int, int> _map({std::pair<int, int>{11, 2}, {99, 0}});
  s21::map<int, int> map_copy(_map);
  auto j = map_copy.begin();
  for (auto i = _map.begin(); i != _map.end(); ++i) {
    ASSERT_TRUE(i->key_ == j->key_);
    ASSERT_TRUE(i->data_ == j->data_);
    ++j;
  }
}

TEST(map_constructor, move) {
  s21::map<int, int> _map({std::pair<int, int>{11, 2}, {99, 0}});
  s21::map<int, int> map_copy(_map);
  s21::map<int, int> map_moved(std::move(_map));
  auto j = map_moved.begin();
  for (auto i = map_copy.begin(); i != map_copy.end(); ++i) {
    ASSERT_TRUE(i->key_ == j->key_);
    ASSERT_TRUE(i->data_ == j->data_);
    ++j;
  }
  EXPECT_EQ(_map.empty(), 1);
}

TEST(map_operator, move_assignment) {
  s21::map<std::string, char> first({std::pair<std::string, char>{"this", 'k'},
                                     {"world", 'o'},
                                     {"is mine", '!'}});
  s21::map<std::string, char> copy(first);
  s21::map<std::string, char> second;
  second = std::move(first);
  auto j = second.begin();
  for (auto i = copy.begin(); i != copy.end(); ++i) {
    ASSERT_TRUE(i->key_ == j->key_);
    ASSERT_TRUE(i->data_ == j->data_);
    ++j;
  }
  EXPECT_EQ(first.empty(), 1);
}

TEST(map_operator, braces) {
  s21::map<int, int> _map;
  _map[0];
  _map[9] = 123;
  EXPECT_EQ(_map[0], 0);
  EXPECT_EQ(_map[9], 123);
}

TEST(map_at, at) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  EXPECT_EQ(_map.at("this"), 'k');
  EXPECT_EQ(_map.at("world"), 'o');
  EXPECT_EQ(_map.at("is mine"), '!');
  EXPECT_THROW(_map.at("something"), std::out_of_range);
  EXPECT_THROW(_map.at("aaa"), std::out_of_range);
}

TEST(map_iterator, begin) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  auto i = _map.begin();
  EXPECT_EQ(i->key_, "is mine");
  EXPECT_EQ(i->data_, '!');
}

TEST(map_iterator, end) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  auto check = _map.end();
  auto iter = _map.begin();
  for (; iter != _map.end(); iter++) {
  }
  ASSERT_TRUE(check == iter);
}

TEST(map_iterator_operator, increment) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  auto i = _map.begin();
  ++i;
  EXPECT_EQ(i->key_, "this");
  EXPECT_EQ(i->data_, 'k');
  i++;
  EXPECT_EQ(i->key_, "world");
  EXPECT_EQ(i->data_, 'o');
}

TEST(map_iterator_operator, decrement_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.begin();
  for (auto iter = _map.begin(); iter != _map.end(); iter++) {
    i = iter;
  }
  EXPECT_EQ(i->key_, 5);
  EXPECT_EQ(i->data_, 4);
  i--;
  EXPECT_EQ(i->key_, 4);
  EXPECT_EQ(i->data_, 3);
}

TEST(map_iterator_operator, decrement_test_1) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.begin();
  int j = 5;
  for (auto iter = _map.begin(); iter != _map.end(); iter++) {
    i = iter;
  }
  while (i != _map.begin()) {
    EXPECT_EQ(i->key_, j);
    --i;
    --j;
  }
}

TEST(map_size, size_check) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  EXPECT_EQ(_map.size(), 5);
  _map.clear();
  EXPECT_EQ(_map.empty(), 1);
  EXPECT_EQ(_map.max_size(), std::numeric_limits<size_t>::max() /
                                 sizeof(std::pair<const int, int>));
  EXPECT_EQ(_map.size(), 0);
}

TEST(map_insert, insert_test_0) {
  s21::map<int, int> _map;
  _map.insert(0, 9);
  auto i = _map.begin();
  EXPECT_EQ(i->key_, 0);
  EXPECT_EQ(i->data_, 9);
}

TEST(map_insert, insert_test_1) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  _map.insert(5, 9);
  EXPECT_EQ(_map[5], 4);
}

TEST(map_insert, insert_value_type_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  _map.insert(std::pair<int, int>(9, 7));
  EXPECT_EQ(_map[9], 7);
}

TEST(map_insert, insert_or_assign_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  _map.insert_or_assign(5, 9);
  EXPECT_EQ(_map[5], 9);
}

TEST(map_insert, insert_many_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{15, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto v =
      _map.insert_many(std::pair<int, int>{5, 9}, std::pair<int, int>{2, 9},
                       std::pair<int, int>{7, 3});
  EXPECT_EQ(_map[5], 9);
  EXPECT_EQ(_map[7], 3);
  EXPECT_EQ(_map[2], 1);
  EXPECT_EQ(v[0].second, 1);
  EXPECT_EQ(v[1].second, 0);
  EXPECT_EQ(v[2].second, 1);
}

TEST(map_erase, erase_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert(8, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(8), std::out_of_range);
}

TEST(map_erase, erase_test_1) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert_or_assign(5, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(5), std::out_of_range);
}

TEST(map_erase, erase_test_2) {
  s21::map<int, int> _map;
  auto i = _map.insert(5, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(5), std::out_of_range);
}

TEST(map_erase, erase_test_3) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert_or_assign(1, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(1), std::out_of_range);
}

TEST(map_erase, erase_test_4) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert_or_assign(4, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(4), std::out_of_range);
}

TEST(map_erase, erase_test_5) {
  s21::map<int, int> _map({std::pair<int, int>{5, 4},
                           {1, 0},
                           {2, 1},
                           {9, 3},
                           {7, 3},
                           {17, 3},
                           {3, 2}});
  auto i = _map.insert_or_assign(5, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(5), std::out_of_range);
}

TEST(map_swap, swap_test_0) {
  s21::map<std::string, char> one(
      {std::pair<std::string, char>{"one", '1'}, {"two", '2'}, {"three", '3'}});
  s21::map<std::string, char> another(
      {std::pair<std::string, char>{"this", 'k'},
       {"world", 'o'},
       {"is mine", '!'},
       {"horse", '.'}});
  s21::map<std::string, char> one_copy(one);
  s21::map<std::string, char> another_copy(another);
  one.swap(another);
  auto j = another.begin();
  for (auto i = one_copy.begin(); i != one_copy.end(); ++i) {
    ASSERT_TRUE(i->key_ == j->key_);
    ASSERT_TRUE(i->data_ == j->data_);
    ++j;
  }
  j = one.begin();
  for (auto i = another_copy.begin(); i != another_copy.end(); ++i) {
    ASSERT_TRUE(i->key_ == j->key_);
    ASSERT_TRUE(i->data_ == j->data_);
    ++j;
  }
}

TEST(map_merge, merge_test_0) {
  s21::map<int, int> _first(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  s21::map<int, int> _second({std::pair<int, int>{-50, 4},
                              {10, 0},
                              {-20, 1},
                              {40, 3},
                              {-30, 2},
                              {5, 5},
                              {2, 2}});
  s21::map<int, int> _result({std::pair<int, int>{5, 4},
                              {1, 0},
                              {2, 1},
                              {4, 3},
                              {3, 2},
                              {-50, 4},
                              {10, 0},
                              {-20, 1},
                              {40, 3},
                              {-30, 2},
                              {5, 5},
                              {2, 2}});
  _first.merge(_second);
  auto it = _first.begin();
  for (auto i = _result.begin(); i != _result.end(); ++i) {
    EXPECT_EQ(i->key_, it->key_);
    EXPECT_EQ(i->data_, it->data_);
    ++it;
  }
}

TEST(map_contains, contains_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  ASSERT_TRUE(!_map.contains(789));
  ASSERT_TRUE(_map.contains(5));
}
