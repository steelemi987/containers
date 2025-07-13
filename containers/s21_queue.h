#ifndef S21_QUEUE_H
#define S21_QUEUE_H

namespace s21 {

template <typename T>
class queue : protected list<T> {
 public:
  // Queue Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // Queue Member functions
  queue(){};
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& s);
  queue(queue&& s);
  ~queue(){};
  queue& operator=(queue&& s);

  // Queue Element access
  const_reference front();
  const_reference back();

  // Queue Capacity
  bool empty();
  size_type size();

  // Queue Modifiers
  void push(const_reference value);
  void pop();
  void swap(queue& other);

  // Insert many
  template <typename... Args>
  void insert_many_back(Args&&... args);
};
}  // namespace s21

#include "s21_queue.tpp"

#endif