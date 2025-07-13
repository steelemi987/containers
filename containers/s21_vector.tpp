#ifndef S21_CONTAINERS_VECTOR_TPP
#define S21_CONTAINERS_VECTOR_TPP

//#include "s21_tests.h"

namespace s21 {

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : arr(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  std::copy(items.begin(), items.end(), arr);
}

template <typename T>
vector<T>::vector(const vector &v)
    : arr(nullptr), size_(v.size_), capacity_(v.size_) {
  if (size_ > 0) {
    arr = new value_type[size_];
  }
  std::copy(v.arr, v.arr + v.size_, arr);
}

template <typename T>
vector<T>::vector(vector &&v) noexcept
    : arr(v.arr), size_(v.size_), capacity_(v.capacity_) {
  v.arr = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] arr;
  arr = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
  if (this != &v) {
    delete[] arr;
    arr = v.arr;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.arr = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range");
  return arr[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range");
  return arr[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (size_ == 0) throw std::out_of_range("Vector is empty");
  return arr[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (size_ == 0) throw std::out_of_range("Vector is empty");
  return arr[size_ - 1];
}

template <typename T>
T *vector<T>::data() {
  return arr;
}

// iterators
template <typename T>
typename vector<T>::iterator vector<T>::begin() const {
  return arr;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() const {
  return arr + size_;
}

// capacity
template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::out_of_range("New size is too large");
  }
  if (size > capacity_) {
    iterator temp = new value_type[size];
    for (size_type i = 0; i < size_; ++i) {
      temp[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = temp;
    capacity_ = size;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    iterator temp = new value_type[size_];
    for (size_type i = 0; i < size_; ++i) {
      temp[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = temp;
    capacity_ = size_;
  }
}

// modifiers
template <typename T>
void vector<T>::clear() {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - arr;
  if (size_ >= capacity_) {
    size_type new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
    reserve(new_capacity);
  }
  std::move_backward(arr + index, arr + size_, arr + size_ + 1);
  arr[index] = value;
  ++size_;
  return arr + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type index = pos - arr;
  if (index > size_) {
    throw std::out_of_range("Index out of range");
  }
  std::move(arr + index + 1, arr + size_, arr + index);
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    size_type new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
    reserve(new_capacity);
  }
  arr[size_] = value;
  ++size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ == 0) {
    throw std::length_error("Nothing to pop_back");
  }
  if (size_ > 0) --size_;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(arr, other.arr);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// insert_many
template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  vector<value_type> temp{args...};
  iterator cur_pos = begin() + (pos - begin());
  for (size_t i = 0; i < temp.size(); ++i) {
    cur_pos = insert(cur_pos, temp[i]);
    ++cur_pos;
  }
  return cur_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(end(), args...);
}

};  // namespace s21

#endif
