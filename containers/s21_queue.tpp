#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

namespace s21 {

// Queue Member functions
template <typename T>
queue<T>::queue(std::initializer_list<value_type> const& items)
    : list<T>(items) {}

template <typename T>
queue<T>::queue(const queue& s) : list<T>(s) {}

template <typename T>
queue<T>::queue(queue&& s) : list<T>(std::move(s)) {}

template <typename T>
typename queue<T>::queue& queue<T>::operator=(queue&& s) {
  list<T>::operator=(std::move(s));
  return *this;
}

// Queue Element access
template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  return list<T>::front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  return list<T>::back();
}

// Queue Capacity
template <typename T>
bool queue<T>::empty() {
  return list<T>::empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return list<T>::size();
}

// Queue Modifiers
template <typename T>
void queue<T>::push(const_reference value) {
  list<T>::push_back(value);
}

template <typename T>
void queue<T>::pop() {
  list<T>::pop_front();
}

template <typename T>
void queue<T>::swap(queue& other) {
  list<T>::swap(other);
}

// Insert many

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args&&... args) {
  list<T>::insert_many_back(args...);
}
}  // namespace s21

#endif