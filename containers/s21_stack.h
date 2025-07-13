#ifndef S21_STACK_H
#define S21_STACK_H

namespace s21 {
template <typename T>
class stack : protected list<T> {
 public:
  // Stack Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // Stack Member functions
  stack(){};
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& s);
  stack(stack&& s);
  ~stack(){};
  stack& operator=(stack&& s);

  // Stack Element access
  const_reference top();

  // Stack Capacity
  bool empty();
  size_type size();

  // Stack Modifiers
  void push(const_reference value);
  void pop();
  void swap(stack& other);

  // Insert many
  template <typename... Args>
  void insert_many_front(Args&&... args);
};
}  // namespace s21

#include "s21_stack.tpp"

#endif  // !S21_STACK_H
