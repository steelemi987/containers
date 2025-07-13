#ifndef S21_SET_H
#define S21_SET_H

#include "s21_bi_tree.h"
#include "s21_vector.h"

namespace s21 {

template <class Key>
class set : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, Key>::iterator;
  using const_iterator = typename BinaryTree<Key, Key>::const_iterator;
  using size_type = size_t;
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();
  set operator=(set&& s);
  iterator begin() const;
  iterator end() const;
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
  bool contains(const Key& key);
  iterator find(const Key& key);
};
};  // namespace s21

#include "s21_set.tpp"

#endif  // S21_SET_H