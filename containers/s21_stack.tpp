#ifndef S21_STACK_TPP
#define S21_STACK_TPP

namespace s21 {

// Stack Member functions
template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items)
    : list<T>(items) {}

template <typename T>
stack<T>::stack(const stack& s) : list<T>(s) {}

template <typename T>
stack<T>::stack(stack&& s) : list<T>(std::move(s)) {}

template <typename T>
typename stack<T>::stack& stack<T>::operator=(stack&& s) {
  list<T>::operator=(std::move(s));
  return *this;
}

// Stack Element access
template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  return list<T>::back();
}

// Stack Capacity
template <typename T>
bool stack<T>::empty() {
  return list<T>::empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return list<T>::size();
}

// Stack Modifiers
template <typename T>
void stack<T>::push(const_reference value) {
  list<T>::push_back(value);
}

template <typename T>
void stack<T>::pop() {
  list<T>::pop_back();
}

template <typename T>
void stack<T>::swap(stack& other) {
  list<T>::swap(other);
}

// Insert many

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args&&... args) {
  list<T>::insert_many_back(args...);
}
}  // namespace s21

#endif