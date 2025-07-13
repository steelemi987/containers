#ifndef S21_LIST_H
#define S21_LIST_H

namespace s21 {
template <typename T>
class list {
 public:
  // List member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  class ListIterator;
  using iterator = ListIterator;
  class ListConstIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  // Functions
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(list&& l);

  // List Element access
  const_reference front();
  const_reference back();

  // List Iterators
  iterator begin();
  iterator end();
  const_iterator const_begin() const;
  const_iterator const_end() const;

  // List Capacity
  bool empty();
  size_type size();
  size_type max_size();  // TODO

  // List Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  // insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  struct Node {
    value_type data_;
    Node* next_;
    Node* prev_;

    Node(const value_type& value)
        : data_(value), next_(nullptr), prev_(nullptr){};

    // bool operator==(Node* other) const {
    //	return this->data_ == other->data_;
    // }

    // bool operator!=(Node* other) const {
    //	return this->data_ == other->data_;
    // }
  };

  Node* front_;
  Node* back_;
  size_type size_;
};

template <typename T>
class list<T>::ListIterator {
 public:
  using value_type = T;
  using reference = T&;

  ListIterator(typename list<value_type>::Node* node) : node_(node){};

  reference operator*() const { return node_->data_; }

  ListIterator& operator++() {
    node_ = node_->next_;
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  ListIterator& operator--() { node_ = node_->prev_; }

  bool operator==(const ListIterator& other) const {
    return this->node_ == other.node_;
  }

  bool operator!=(const ListIterator& other) const {
    return this->node_ != other.node_;
  }

  typename list<T>::Node* getNode() { return node_; }

 private:
  typename list<value_type>::Node* node_;
};

template <typename T>
class list<T>::ListConstIterator {
 public:
  using value_type = T;
  using reference = const T&;

  ListConstIterator(const typename list<value_type>::Node* node)
      : node_(node){};

  reference operator*() const { return node_->data_; }

  ListConstIterator& operator++() {
    node_ = node_->next_;
    return *this;
  }

  ListConstIterator operator++(int) {
    ListConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  ListConstIterator& operator--() { node_ = node_->prev_; }

  bool operator==(const ListConstIterator& other) const {
    return this->node_ == other.node_;
  }

  bool operator!=(const ListConstIterator& other) const {
    return this->node_ != other.node_;
  }

  const typename list<T>::Node* getConstNode() { return node_; }

 private:
  const typename list<value_type>::Node* node_;
};
}  // namespace s21

#include "s21_list.tpp"

#endif