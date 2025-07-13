#ifndef S21_array_TPP
#define S21_array_TPP

namespace s21 {

// Array Member functions

template <typename T, size_t N>
array<T, N>::array() : vector<T>(N) {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items)
    : vector<T>(items) {}

template <typename T, size_t N>
array<T, N>::array(const array& a) : vector<T>(a) {}

template <typename T, size_t N>
array<T, N>::array(array&& a) : vector<T>(std::move(a)) {}

template <typename T, size_t N>
typename array<T, N>::array& array<T, N>::operator=(array&& a) {
  vector<T>::operator=(std::move(a));
  return *this;
}

// array Element access
template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  return vector<T>::at(pos);
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return vector<T>::operator[](pos);
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return vector<T>::front();
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return vector<T>::back();
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return vector<T>::data();
}

// Array Iterators
template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return vector<T>::begin();
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return vector<T>::end();
}

// array Capacity
template <typename T, size_t N>
bool array<T, N>::empty() {
  return vector<T>::empty();
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return vector<T>::size();
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return vector<T>::capacity();
}

// array Modifiers

template <typename T, size_t N>
void array<T, N>::swap(array& other) {
  vector<T>::swap(other);
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  int s = size();
  this->clear();
  for (int i = 0; i < s; i++) {
    vector<T>::push_back(value);
  }
}
}  // namespace s21

#endif