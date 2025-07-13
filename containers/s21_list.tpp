#ifndef S21_LIST_TPP
#define S21_LIST_TPP

namespace s21 {

// Functions

template <typename T>
list<T>::list() : front_(nullptr), back_(nullptr), size_(0){};

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
};

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const auto& item : items) {
    push_back(item);
  }
};

template <typename T>
list<T>::list(const list& l) : list() {
  for (auto i = l.const_begin(); i != l.const_end(); ++i) {
    push_back(*i);
  }
};

template <typename T>
list<T>::list(list&& l) : front_(l.front_), back_(l.back_), size_(l.size_) {
  l.front_ = nullptr;
  l.back_ = nullptr;
  l.size_ = 0;
};

template <typename T>
list<T>::~list() {
  while (front_ != nullptr) {
    Node* tmp = front_;
    front_ = front_->next_;
    delete tmp;
  }
  back_ = nullptr;
  size_ = 0;
};

template <typename T>
typename list<T>::list& list<T>::operator=(list&& l) {
  if (this != &l) {
    clear();
    front_ = l.front_;
    back_ = l.back_;
    size_ = l.size_;
    l.front_ = nullptr;
    l.back_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

// List Element access
template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (size_ == 0) {
    throw std::out_of_range("Empty list");
  }
  return front_->data_;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (size_ == 0) {
    throw std::out_of_range("Empty list");
  }
  return back_->data_;
}

// List Iterators
template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(front_);
}

template <typename T>
typename list<T>::const_iterator list<T>::const_begin() const {
  return const_iterator(front_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(back_->next_);
}

template <typename T>
typename list<T>::const_iterator list<T>::const_end() const {
  return const_iterator(back_->next_);
}

// List Capacity
template <typename T>
bool list<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

// List Modifiers

template <typename T>
void list<T>::clear() {
  while (front_ != nullptr) {
    Node* tmp = front_;
    front_ = front_->next_;
    delete tmp;
  }
  back_ = nullptr;
  size_ = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* node = new Node(value);
  if (pos == this->begin()) {
    node->next_ = front_;
    if (front_ != nullptr) {
      front_->prev_ = node;
    }
    front_ = node;
    if (back_ == nullptr) {
      back_ = node;
    }
  } else if (pos == this->end()) {
    back_->next_ = node;
    node->prev_ = back_;
    back_ = node;
  } else {
    Node* current = pos.getNode();
    node->next_ = current;
    node->prev_ = current->prev_;
    current->prev_->next_ = node;
    current->prev_ = node;
  }
  size_++;
  return iterator(node);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (!empty()) {
    Node* node = pos.getNode();
    if (node == this->front_) {
      front_ = front_->next_;
      if (front_ != nullptr) {
        front_->prev_ = nullptr;
      }
    } else if (node == this->back_) {
      back_ = back_->prev_;
      back_->next_ = nullptr;
    } else {
      node->prev_->next_ = node->next_;
      node->next_->prev_ = node->prev_;
    }
    delete node;
    size_--;
  } else {
    throw std::out_of_range("Empty list");
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* node = new Node(value);
  if (this->empty()) {
    front_ = node;
    back_ = node;
  } else {
    node->prev_ = back_;
    back_->next_ = node;
    back_ = node;
  }
  size_++;
}

// template <typename T>
// void list<T>::push_back(const_reference value) {
//	iterator p = this->begin();
//	while (p.getNode() != back_) {
//		p++;
//	}
//	insert(p, value);
// }

template <typename T>
void list<T>::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("Empty list");
  }
  iterator p = this->begin();
  while (p.getNode() != back_) {
    p++;
  }
  this->erase(p);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  this->insert(this->begin(), value);
}

template <typename T>
void list<T>::pop_front() {
  if (size_ == 0) {
    throw std::out_of_range("Empty list");
  }
  this->erase(this->begin());
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list& other) {
  if (this != &other) {
    this->sort();
    other.sort();
    auto i = this->begin();
    auto k = other.begin();
    while (k != other.end()) {
      if (i == this->end() || *k < *i) {
        this->insert(i, *k);
        ++k;
      } else {
        ++i;
      }
    }
    other.clear();
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  iterator iter = this->begin();
  for (iter = this->begin(); iter != this->end(); iter++) {
    if (iter.getNode() == pos.getConstNode()) {
      break;
    }
  }
  for (auto i = other.begin(); i != other.end(); i++) {
    this->insert(iter, *i);
  }
  other.clear();
}

template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node* tmp_1 = front_;
    Node* tmp_2 = back_;
    while (tmp_1 != tmp_2 && tmp_1->prev_ != tmp_2) {
      std::swap(tmp_1->data_, tmp_2->data_);
      tmp_1 = tmp_1->next_;
      tmp_2 = tmp_2->prev_;
    }
  }
}

template <typename T>
void list<T>::unique() {
  if (size_ > 1) {
    Node* current = front_->next_;
    Node* prev = front_;
    while (current != nullptr) {
      if (current->data_ == prev->data_) {
        Node* node = current->next_;
        erase(current);
        current = node;
      } else {
        prev = current;
        current = current->next_;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    bool flag = true;
    Node* current;
    Node* lastSorted = nullptr;
    do {
      flag = false;
      current = front_;
      while (current->next_ != lastSorted) {
        if (current->data_ > current->next_->data_) {
          std::swap(current->data_, current->next_->data_);
          flag = true;
        }
        current = current->next_;
      }
      lastSorted = current;
    } while (flag);
  }
}

// insert_many

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator i(const_cast<Node*>(pos.getConstNode()));
  for (const auto& arg : {args...}) {
    insert(i, arg);
  }
  return i;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  insert_many(const_end(), args...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  insert_many(const_begin(), args...);
}
}  // namespace s21

#endif