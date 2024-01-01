
#include <iostream>
#include <algorithm>
#include <string.h>

template <typename K, typename V>
class HashMap {

public:
  struct Node {
    K key;
    V value;

    Node *next = nullptr;

    Node() {}
    Node(const K &key, const V &value, Node *next) : key(key), value(value), next(next) {}
    Node(Node &other) {
      this->key = other.key;
      this->value = other.value;
      this->isEmpty = other.isEmpty;
      this->next = other.next;
    }
  };

  HashMap(size_t initial_size);
  ~HashMap();

  bool Insert(const K &key, const V &value);
  const V *Get(const K &key);
  bool Contains(const K &key);
  bool Remove(const K &key);
  size_t Size();
  bool Empty();
  size_t Capacity();
  void Print();

private:
  Node **arr;
  size_t size;
  size_t capacity;
  std::hash<K> hashFunction;
};

template <typename K, typename V>
HashMap<K, V>::HashMap(size_t initial_size) {
  arr = new Node * [initial_size];
  memset(arr, 0, sizeof(Node *) * initial_size);
  size = 0;
  capacity = initial_size;
}

template <typename K, typename V>
HashMap<K, V>::~HashMap() {
  for (size_t i = 0; i < capacity; ++i) {
    Node *curr = arr[i];
    while (curr) {
      Node *temp = curr;
      curr = curr->next;
      delete temp;
    }
  }
  delete[] arr;
}

template <typename K, typename V>
bool HashMap<K, V>::Insert(const K &key, const V &value) {
  if (size == capacity) {
    return false;
  }

  size_t idx = hashFunction(key) % capacity;
  Node *newNode = new Node(key, value, arr[idx]);
  if (arr[idx] != nullptr) {
    newNode->next = arr[idx];
  }

  arr[idx] = newNode;
  ++size;
  return true;
}

template <typename K, typename V>
const V *HashMap<K, V>::Get(const K &key) {
  size_t idx = hashFunction(key) % capacity;

  Node *curr = arr[idx];
  while (curr != nullptr) {
    if (curr->key == key) {
      return &curr->value;
    }
    curr = curr->next;
  }

  return nullptr;
}

template <typename K, typename V>
size_t HashMap<K, V>::Size() {
  return size;
}

template <typename K, typename V>
bool HashMap<K, V>::Empty() {
  return size == 0;
}

template <typename K, typename V>
size_t HashMap<K, V>::Capacity() {
  return capacity;
}

template <typename K, typename V>
bool HashMap<K, V>::Contains(const K &key) {
  return Get(key) != nullptr;
}

template <typename K, typename V>
bool HashMap<K, V>::Remove(const K &key) {
  size_t idx = hashFunction(key) % capacity;
  if (arr[idx] == nullptr) {
    return false;
  }

  Node *curr = arr[idx];
  while (curr->next != nullptr) {
    if (curr->key == key) {
      curr->key = curr->next->key;
      curr->value = curr->next->value;
      curr->next = curr->next->next;
      --size;
      return true;
    }
    curr = curr->next;
  }

  return false;
}

template <typename K, typename V>
void HashMap<K, V>::Print() {
  Node *curr = nullptr;
  for (size_t i = 0; i < capacity; i++) {
    std::cout << "arr[" << i << "] -> ";
    curr = arr[i];
    while (curr != nullptr) {
      std::cout << "(" << curr->key << ", " << curr->value << ") -> ";
      curr = curr->next;
    }
    std::cout << std::endl;
  }
}
