#pragma once

#include <exception>

namespace static_containers {

class Memory {
  Memory(size_t size) : address(nullptr), size(size), is_used(false) {
    address = static_cast<unsigned char *>(malloc(size));
    if (address == nullptr)
      throw std::bad_alloc();
  }

public:
  ~Memory() {
    if (address != nullptr)
      free(address);
  }

  unsigned char *address;
  size_t size;
  bool is_used;

  static Memory make_memory(size_t size) { return Memory(size); }
};
} // namespace static_containers
