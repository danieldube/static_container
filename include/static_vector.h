#pragma once

#include <memory.h>

namespace static_containers {
template <typename Content> class StaticVector {
public:
  using value_type = Content;

  explicit StaticVector(Memory &memory)
      : memory(memory), token(memory.allocate()){};

  size_t capacity() const { return memory.size / sizeof(value_type); }

  void push_back(Content content) {
    auto &element = get_element(size);
    element = std::move(content);
    ++size;
  }

  value_type &operator[](size_t index) {
    if (index >= size)
      throw std::range_error("Index is out of size.");
    return get_element(index);
  }

private:
  const Memory &memory;
  Memory::Token token;

  size_t size{0};

  Content &get_element(size_t index) {
    size_t location = index * sizeof(Content);
    if (location >= memory.size)
      throw std::range_error("Index is out of capacity.");
    auto pointer = (value_type *)(memory.address + location);
    return *pointer;
  }
};
} // namespace static_containers
