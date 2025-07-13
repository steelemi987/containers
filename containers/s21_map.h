#ifndef S21_MAP_H
#define S21_MAP_H

#include "s21_bi_tree.h"
#include "s21_vector.h"

namespace s21 {

template <class Key, class T>
class map : public BinaryTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, T>::iterator;
  using const_iterator = typename BinaryTree<Key, T>::const_iterator;
  using size_type = size_t;
  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();
  map operator=(map&& m);
  T& at(const Key& key);
  T& operator[](const Key& key);
  iterator begin() const;
  iterator end() const;
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  bool contains(const Key& key);
};
};  // namespace s21

#include "s21_map.tpp"

#endif  // S21_MAP_H