#ifndef S21_MAP_TPP
#define S21_MAP_TPP

//#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map() : BinaryTree<Key, T>() {}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items)
    : BinaryTree<Key, T>(items) {}

template <typename Key, typename T>
map<Key, T>::map(const map& m) : BinaryTree<Key, T>(m) {}

template <typename Key, typename T>
map<Key, T>::map(map&& m) : BinaryTree<Key, T>(std::move(m)) {}

template <typename Key, typename T>
map<Key, T>::~map() {}

template <typename Key, typename T>
map<Key, T> map<Key, T>::operator=(map&& m) {
  BinaryTree<Key, T>::operator=(std::move(m));
  return *this;
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return BinaryTree<Key, T>::operator[](key);
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  return BinaryTree<Key, T>::at(key);
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  return BinaryTree<Key, T>::contains(key);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  return BinaryTree<Key, T>::insert(value);
}

template <typename Key, typename T>
bool map<Key, T>::empty() {
  return BinaryTree<Key, T>::empty();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  return BinaryTree<Key, T>::insert(key, obj);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  return BinaryTree<Key, T>::insert_or_assign(key, obj);
}

template <typename Key, typename T>
template <typename... Args>
s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> result_vector;
  for (const auto& arg : {args...}) {
    result_vector.push_back(insert(arg));
  }
  return result_vector;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() const {
  return BinaryTree<Key, T>::begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() const {
  return BinaryTree<Key, T>::end();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  return BinaryTree<Key, T>::size();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return BinaryTree<Key, T>::max_size();
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  BinaryTree<Key, T>::clear();
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  BinaryTree<Key, T>::erase(pos);
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  BinaryTree<Key, T>::swap(other);
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  BinaryTree<Key, T>::merge(other);
}

};  // namespace s21

#endif