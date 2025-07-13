#ifndef S21_BI_TREE_CPP
#define S21_BI_TREE_CPP
#include "s21_bi_tree.h"

namespace s21 {

template <typename K, typename T>
BinaryTree<K, T>::Node::Node(key_type key, mapped_type data, Node* parent)
    : key_(key),
      data_(data),
      left_(nullptr),
      right_(nullptr),
      parent_(parent) {}

template <typename K, typename T>
BinaryTree<K, T>::Node::~Node() noexcept {
  if (left_) delete left_;
  if (right_) delete right_;
}

template <typename K, typename T>
BinaryTree<K, T>::Iterator::Iterator() : node_ptr_(nullptr), stub_(nullptr) {}

template <typename K, typename T>
BinaryTree<K, T>::Iterator::Iterator(Node* node_ptr, Node* stub_)
    : node_ptr_(node_ptr), stub_(stub_) {}

template <typename K, typename T>
typename BinaryTree<K, T>::Iterator& BinaryTree<K, T>::Iterator::operator++() {
  if (node_ptr_) {
    if (node_ptr_->right_) {
      node_ptr_ = node_ptr_->right_;
      while (node_ptr_->left_) {
        node_ptr_ = node_ptr_->left_;
      }
    } else if (node_ptr_->parent_) {
      int end = 1;
      while (node_ptr_->parent_ && end) {
        if (node_ptr_->parent_->left_ == node_ptr_) {
          end = 0;
        }
        node_ptr_ = node_ptr_->parent_;
      }
      if (end) {
        node_ptr_ = stub_;
      }
    } else {
      node_ptr_ = stub_;
    }
  } else if (node_ptr_ == nullptr) {
    node_ptr_ = stub_;
  }
  return *this;
}

template <typename K, typename T>
typename BinaryTree<K, T>::Iterator BinaryTree<K, T>::Iterator::operator++(
    int) {
  Iterator tmp(node_ptr_, stub_);
  ++(*this);
  return tmp;
}
template <typename K, typename T>
typename BinaryTree<K, T>::Iterator& BinaryTree<K, T>::Iterator::operator--() {
  if (node_ptr_) {
    if (node_ptr_->left_) {
      node_ptr_ = node_ptr_->left_;
      while (node_ptr_->right_) {
        node_ptr_ = node_ptr_->right_;
      }
    } else if (node_ptr_->parent_) {
      int end = 1;
      while (node_ptr_->parent_ && end) {
        if (node_ptr_->parent_->right_ == node_ptr_) {
          end = 0;
        }
        node_ptr_ = node_ptr_->parent_;
      }
    }
  }
  return *this;
}

template <typename K, typename T>
typename BinaryTree<K, T>::Iterator BinaryTree<K, T>::Iterator::operator--(
    int) {
  Iterator tmp(node_ptr_, stub_);
  --(*this);
  return tmp;
}

template <typename K, typename T>
bool BinaryTree<K, T>::Iterator::operator==(Iterator other) const {
  return this->node_ptr_ == other.node_ptr_;
}

template <typename K, typename T>
bool BinaryTree<K, T>::Iterator::operator!=(Iterator other) const {
  return this->node_ptr_ != other.node_ptr_;
}

template <typename K, typename T>
typename BinaryTree<K, T>::Node* BinaryTree<K, T>::Iterator::operator->()
    const {
  return node_ptr_;
}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree() : stub_(new Node(key_type(), mapped_type())) {}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree(std::initializer_list<value_type> const& items)
    : stub_(new Node(key_type(), mapped_type())) {
  for (auto i = items.begin(); i != items.end(); ++i)
    insert(i->first, i->second);
}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree(const BinaryTree& other)
    : stub_(new Node(key_type(), mapped_type())) {
  for (auto i = other.begin(); i != other.end(); ++i) {
    insert_rek(root_.node_ptr_, i->key_, i->data_);
  }
}

template <typename K, typename T>
BinaryTree<K, T>::BinaryTree(BinaryTree&& other)
    : stub_(new Node(key_type(), mapped_type())) {
  *this = std::move(other);
}

template <typename K, typename T>
BinaryTree<K, T> BinaryTree<K, T>::operator=(BinaryTree&& other) {
  if (this != &other) {
    if (stub_) delete stub_;
    root_.node_ptr_ = other.root_.node_ptr_;
    stub_ = other.stub_;
    other.root_.node_ptr_ = nullptr;
    other.stub_ = nullptr;
  }
  return *this;
}

template <typename K, typename T>
BinaryTree<K, T>::~BinaryTree() {
  if (stub_) delete stub_;
  if (root_.node_ptr_) delete root_.node_ptr_;
  stub_ = nullptr;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::begin() const {
  iterator begin(root_.node_ptr_, stub_);
  if (root_.node_ptr_) {
    while (begin->left_) {
      begin.node_ptr_ = begin->left_;
    }
  } else {
    begin.node_ptr_ = stub_;
  }
  return begin;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::end() const {
  return iterator(stub_, stub_);
}

template <typename K, typename T>
typename BinaryTree<K, T>::size_type BinaryTree<K, T>::size() {
  size_type size_ = 0;
  for (auto i = begin(); i != end(); ++i) {
    size_++;
  }
  return size_;
}

template <typename K, typename T>
typename BinaryTree<K, T>::size_type BinaryTree<K, T>::max_size() {
  return std::numeric_limits<typename BinaryTree<K, T>::size_type>::max() /
         sizeof(typename BinaryTree<K, T>::value_type);
}

template <typename K, typename T>
bool BinaryTree<K, T>::empty() {
  size_type size_ = size();
  return size_ == 0;
}

template <typename K, typename T>
void BinaryTree<K, T>::clear() {
  if (root_.node_ptr_) delete root_.node_ptr_;
  root_.node_ptr_ = nullptr;
  root_.stub_ = nullptr;
  if (stub_) delete stub_;
  stub_ = nullptr;
}

template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator, bool> BinaryTree<K, T>::insert(
    const value_type& value) {
  return insert(value.first, value.second);
}

template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator, bool> BinaryTree<K, T>::insert(
    const K& key, const T& obj) {
  std::pair<iterator, bool> res_p;
  res_p.first.node_ptr_ = find_node_(root_.node_ptr_, key);
  res_p.first.stub_ = stub_;
  res_p.second = false;
  if (res_p.first.node_ptr_ == nullptr) {
    res_p = insert_or_assign(key, obj);
  }
  return res_p;
}

template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator, bool>
BinaryTree<K, T>::insert_or_assign(const K& key, const T& obj) {
  std::pair<iterator, bool> res_p;
  res_p.first.node_ptr_ = find_node_(root_.node_ptr_, key);
  res_p.first.stub_ = stub_;
  if (res_p.first.node_ptr_ == nullptr) {
    res_p.first.node_ptr_ = insert_rek(root_.node_ptr_, key, obj);
    res_p.second = true;
  } else {
    res_p.first.node_ptr_->data_ = obj;
    res_p.second = false;
  }
  return res_p;
}

template <typename K, typename T>
typename BinaryTree<K, T>::Node* BinaryTree<K, T>::insert_rek(Node* root,
                                                              const K& key,
                                                              const T& obj) {
  if (root_.node_ptr_ == nullptr) {
    root_.node_ptr_ = new Node(key, obj, nullptr);
    root_.stub_ = stub_;
    root = root_.node_ptr_;
  } else {
    if (key >= root->key_) {
      if (root->right_ == nullptr) {
        root->right_ = new Node(key, obj, root);
        root = root->right_;
      } else {
        root = insert_rek(root->right_, key, obj);
      }
    } else if (key < root->key_) {
      if (root->left_ == nullptr) {
        root->left_ = new Node(key, obj, root);
        root = root->left_;
      } else {
        root = insert_rek(root->left_, key, obj);
      }
    }
  }
  return root;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::insert(const K& key) {
  iterator iter;
  iter.stub_ = stub_;
  iter.node_ptr_ = insert_rek(root_.node_ptr_, key, K());

  return iter;
}

template <typename K, typename T>
void BinaryTree<K, T>::erase(iterator pos) {
  Node* current = nullptr;
  for (auto i = begin(); i != end(); ++i) {
    if (pos == i) {
      current = i.node_ptr_;
    }
  }
  if (current) {
    if (current->parent_ == nullptr) {
      delete_root(current);
    } else if (current->left_ == nullptr) {
      delete_one(current->parent_, current, current->right_);
    } else if (current->right_ == nullptr) {
      delete_one(current->parent_, current, current->left_);
    } else {
      delete_two(current);
    }
    current->parent_ = nullptr;
    current->right_ = nullptr;
    current->left_ = nullptr;
    delete current;
  }
}

template <typename K, typename T>
void BinaryTree<K, T>::delete_root(Node* current) {
  if (current->left_ == nullptr) {
    root_.node_ptr_ = current->right_;
    if (current->right_) {
      current->right_->parent_ = nullptr;
    }
  } else if (current->right_ == nullptr) {
    root_.node_ptr_ = current->left_;
    if (current->left_) {
      current->left_->parent_ = nullptr;
    }
  } else {
    Node* min = current->right_;
    while (min->left_) {
      min = min->left_;
    }
    if (current->right_ != min) {
      delete_one(min->parent_, min, min->right_);
      min->right_ = current->right_;
      current->right_->parent_ = min;
    }
    min->left_ = current->left_;
    current->left_->parent_ = min;
    min->parent_ = nullptr;
    root_.node_ptr_ = min;
  }
}

template <typename K, typename T>
void BinaryTree<K, T>::delete_one(Node* parent, Node* current, Node* next) {
  if (next == nullptr) {
    if (parent->left_ == current) {
      parent->left_ = nullptr;
    } else if (parent->right_ == current) {
      parent->right_ = nullptr;
    }
  } else {
    if (parent->left_ == current) {
      parent->left_ = next;
    } else if (parent->right_ == current) {
      parent->right_ = next;
    }
    next->parent_ = parent;
  }
}

template <typename K, typename T>
void BinaryTree<K, T>::delete_two(Node* current) {
  Node* min = current->right_;
  while (min->left_) {
    min = min->left_;
  }
  if (current->right_ != min) {
    delete_one(min->parent_, min, min->right_);
    min->right_ = current->right_;
    current->right_->parent_ = min;
  }
  min->left_ = current->left_;
  current->left_->parent_ = min;
  delete_one(current->parent_, current, min);
}

template <typename K, typename T>
void BinaryTree<K, T>::swap(BinaryTree& other) {
  swap_tree(other);
}

template <typename K, typename T>
void BinaryTree<K, T>::merge(BinaryTree& other) {
  fill_tree_another_tree(other);
}

template <typename K, typename T>
bool BinaryTree<K, T>::contains(const K& key) {
  return contains(root_.node_ptr_, key);
}

template <typename K, typename T>
bool BinaryTree<K, T>::contains(Node* root, const K& key) {
  bool res = false;
  if (root) {
    if (key == root->key_) {
      res = true;
    } else if (key < root->key_) {
      res = contains(root->left_, key);
    } else {
      res = contains(root->right_, key);
    }
  }
  return res;
}

template <typename K, typename T>
typename BinaryTree<K, T>::size_type BinaryTree<K, T>::count(const K& key) {
  size_type c = 0;
  for (auto i = begin(); i != end(); ++i)
    if (key == i->key_) c++;
  return c;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::lower_bound(
    const K& key) {
  iterator low;
  int flag = 1;
  for (auto i = begin(); i != end() && flag; ++i) {
    if (i->key_ >= key) {
      low.node_ptr_ = i.node_ptr_;
      flag = 0;
    }
  }
  if (flag) {
    low.node_ptr_ = stub_;
  }
  return low;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::upper_bound(
    const K& key) {
  iterator up;
  int flag = 1;
  for (auto i = begin(); i != end() && flag; ++i) {
    if (i->key_ > key) {
      up.node_ptr_ = i.node_ptr_;
      flag = 0;
    }
  }
  if (flag) {
    up.node_ptr_ = stub_;
  }
  return up;
}

template <typename K, typename T>
std::pair<typename BinaryTree<K, T>::iterator,
          typename BinaryTree<K, T>::iterator>
BinaryTree<K, T>::equal_range(const K& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
}

template <typename K, typename T>
T& BinaryTree<K, T>::at(const K& key) {
  iterator temp;
  temp.node_ptr_ = root_.node_ptr_;
  temp.stub_ = stub_;
  Node* result = find_node_(temp.node_ptr_, key);
  if (result == nullptr) throw std::out_of_range("");
  return result->data_;
}

template <typename K, typename T>
typename BinaryTree<K, T>::iterator BinaryTree<K, T>::find(const K& key) {
  iterator temp(find_node_(root_.node_ptr_, key), stub_);
  return temp;
}

template <typename K, typename T>
typename BinaryTree<K, T>::Node* BinaryTree<K, T>::find_node_(Node* root,
                                                              const K& key) {
  if (root != nullptr && root->key_ != key) {
    if (key < root->key_) {
      root = find_node_(root->left_, key);
    } else if (key > root->key_) {
      root = find_node_(root->right_, key);
    }
  }
  return root;
}

template <typename K, typename T>
T& BinaryTree<K, T>::operator[](const K& key) {
  iterator temp;
  temp.node_ptr_ = root_.node_ptr_;
  temp.stub_ = stub_;
  Node* result = find_node_(temp.node_ptr_, key);
  if (result == nullptr) result = insert_or_assign(key, T()).first.node_ptr_;
  return result->data_;
}

template <typename K, typename T>
void BinaryTree<K, T>::swap_tree(BinaryTree& other) {
  iterator temp_root(root_.node_ptr_, stub_);
  Node* temp_stub = stub_;
  root_.node_ptr_ = other.root_.node_ptr_;
  root_.stub_ = other.root_.stub_;
  stub_ = other.stub_;
  other.root_.node_ptr_ = temp_root.node_ptr_;
  other.root_.stub_ = temp_root.stub_;
  other.stub_ = temp_stub;
}

template <typename K, typename T>
void BinaryTree<K, T>::fill_tree_another_tree(const BinaryTree& other) {
  for (auto i = other.begin(); i != other.end(); ++i) {
    insert(i->key_, i->data_);
  }
}

};  // namespace s21

#endif