#ifndef S21_BI_TREE_H
#define S21_BI_TREE_H

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {
template <typename K, typename T>
class BinaryTree {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  struct Node {
    key_type key_;
    mapped_type data_;
    Node* left_;
    Node* right_;
    Node* parent_;
    Node(key_type key, mapped_type data, Node* parent = nullptr);
    ~Node() noexcept;
  };

  class Iterator {
   public:
    Node* node_ptr_;
    Node* stub_;
    Iterator();
    explicit Iterator(Node* node_ptr, Node* stub_);
    Iterator& operator++();
    Iterator operator++(int);
    Iterator operator--(int);
    Iterator& operator--();
    bool operator==(Iterator other) const;
    bool operator!=(Iterator other) const;
    Node* operator->() const;
  };

  using iterator = Iterator;
  using const_iterator = const Iterator;

  BinaryTree();
  BinaryTree(std::initializer_list<value_type> const& items);
  BinaryTree(const BinaryTree& other);
  BinaryTree(BinaryTree&& other);
  BinaryTree operator=(BinaryTree&& other);
  ~BinaryTree();

  iterator begin() const;
  iterator end() const;
  size_type size();
  size_type max_size();
  bool empty();
  void clear();

 protected:
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const K& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const K& key, const T& obj);
  iterator insert(const K& key);
  void erase(iterator pos);
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);
  bool contains(const K& key);
  size_type count(const K& key);
  iterator find(const K& key);

  iterator lower_bound(const K& key);
  iterator upper_bound(const K& key);
  std::pair<iterator, iterator> equal_range(const K& key);
  T& at(const K& key);
  T& operator[](const K& key);

  iterator root_;

 private:
  Node* stub_;
  void swap_tree(BinaryTree& other);
  void fill_tree_another_tree(const BinaryTree& other);
  Node* find_node_(Node* root, const K& key);
  bool contains(Node* root, const K& key);
  Node* insert_rek(Node* root, const K& key, const T& obj);
  void delete_one(Node* parent, Node* current, Node* next);
  void delete_two(Node* current);
  void delete_root(Node* current);
};
};  // namespace s21

#include "s21_bi_tree.tpp"

#endif