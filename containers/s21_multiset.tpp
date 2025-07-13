#ifndef S21_MULTISET_TPP
#define S21_MULTISET_TPP

#include "s21_multiset.h"
namespace s21 {

template <typename Key>
multiset<Key>::multiset() : BinaryTree<Key, Key>() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : BinaryTree<Key, Key>() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    multiset<Key>::insert(*i);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& ms) : BinaryTree<Key, Key>(ms) {}

template <typename Key>
multiset<Key>::multiset(multiset&& ms) : BinaryTree<Key, Key>(std::move(ms)) {}

template <typename Key>
multiset<Key>::~multiset() {}

template <typename Key>
multiset<Key> multiset<Key>::operator=(multiset&& ms) {
  BinaryTree<Key, Key>::operator=(std::move(ms));
  return *this;
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) {
  return BinaryTree<Key, Key>::contains(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  return BinaryTree<Key, Key>::find(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  return BinaryTree<Key, Key>::insert(value);
}

template <typename Key>
template <typename... Args>
s21::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> result_vector;
  for (const auto& arg : {args...}) {
    result_vector.push_back(std::pair<iterator, bool>{insert(arg), true});
  }
  return result_vector;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  return BinaryTree<Key, Key>::count(key);
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return BinaryTree<Key, Key>::equal_range(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  return BinaryTree<Key, Key>::lower_bound(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  return BinaryTree<Key, Key>::upper_bound(key);
}

template <typename Key>
bool multiset<Key>::empty() {
  return BinaryTree<Key, Key>::empty();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() const {
  return BinaryTree<Key, Key>::begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() const {
  return BinaryTree<Key, Key>::end();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  return BinaryTree<Key, Key>::size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return std::numeric_limits<typename multiset<Key>::size_type>::max() /
         sizeof(typename multiset<Key>::value_type);
}

template <typename Key>
void multiset<Key>::clear() {
  BinaryTree<Key, Key>::clear();
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  BinaryTree<Key, Key>::erase(pos);
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  BinaryTree<Key, Key>::swap(other);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  BinaryTree<Key, Key>::merge(other);
}

};  // namespace s21

#endif