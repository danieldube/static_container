#pragma once

#include "include/memory.h"

namespace static_containers {
template <typename Content> class StaticVector {
public:
  using value_type = Content;

  explicit StaticVector(Memory &memory)
      : memory(memory), token(memory.allocate()){};

  ~StaticVector() {
    while (size_ > 0) {
      auto &element = get_element(size_ - 1);
      element.~value_type();
      size_--;
    }
  }

  StaticVector(StaticVector &&static_vector) noexcept
      : memory(static_vector.memory), token(std::move(static_vector.token)),
        size_(static_vector.size_) {
    static_vector.size_ = 0;
  };

  size_t capacity() const { return memory.size / sizeof(value_type); }

  void push_back(value_type &&arguments) {
    auto *address = get_pointer(size_);
    new (address) value_type(std::move(arguments));
    ++size_;
  }

  void push_back(const value_type &arguments) {
    auto *address = get_pointer(size_);
    new (address) value_type(arguments);
    ++size_;
  }

  value_type &operator[](size_t index) { return get_element(index); }

  const value_type &operator[](size_t index) const {
    const value_type &result = get_element(index);
    return result;
  }

  size_t size() const { return size_; }

private:
  const Memory &memory;
  Memory::Token token;

  size_t size_{0};

  value_type *get_pointer(size_t index) const {
    size_t location = index * sizeof(Content);
    if (location >= memory.size)
      throw std::range_error("Index is out of capacity.");
    auto pointer = (value_type *)(memory.address + location);
    return pointer;
  }

  value_type &get_element(size_t index) const {
    if (index >= size_)
      throw std::range_error("Index is out of size.");
    auto pointer = get_pointer(index);
    return *pointer;
  }
};
} // namespace static_containers
