#pragma once

#include "include/memory.h"

namespace static_containers {
template <typename Content> class StaticVector {
public:
  using value_type = Content;

  explicit StaticVector(Memory &memory)
      : memory(memory), token(memory.allocate()){};

  ~StaticVector() {
    while (size > 0) {
      auto &element = get_element(size - 1);
      element.~value_type();
      size--;
    }
  }

  size_t capacity() const { return memory.size / sizeof(value_type); }

  void push_back(value_type &&arguments) {
    auto *address = get_pointer(size);
    new (address) value_type(std::move(arguments));
    ++size;
  }

  void push_back(const value_type &arguments) {
    auto *address = get_pointer(size);
    new (address) value_type(arguments);
    ++size;
  }

  value_type &operator[](size_t index) { return get_element(index); }

  const value_type &operator[](size_t index) const {
    const value_type &result = get_element(index);
    return result;
  }

private:
  const Memory &memory;
  Memory::Token token;

  size_t size{0};

  value_type *get_pointer(size_t index) const {
    size_t location = index * sizeof(Content);
    if (location >= memory.size)
      throw std::range_error("Index is out of capacity.");
    auto pointer = (value_type *)(memory.address + location);
    return pointer;
  }

  value_type &get_element(size_t index) const {
    if (index >= size)
      throw std::range_error("Index is out of size.");
    auto pointer = get_pointer(index);
    return *pointer;
  }
};
} // namespace static_containers
