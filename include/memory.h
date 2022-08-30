#pragma once

#include <cstdlib>
#include <exception>

namespace static_containers {

class Memory;

class Memory {
  Memory(size_t size) : address(nullptr), size(size), is_used(false) {
    address = static_cast<unsigned char *>(malloc(size));
    if (address == nullptr)
      throw std::bad_alloc();
  }

public:
  class Token {
  public:
    Token(Memory &memory) : memory(memory) {}
    ~Token() { memory.deallocate(); }

  private:
    Memory &memory;
  };

  ~Memory() {
    if (address != nullptr)
      free(address);
  }

  Token allocate() {
    is_used = true;
    return Token(*this);
  }

  void deallocate() { is_used = false; }

  bool isUsed() const { return is_used; }

  Memory(const Memory &memory) = delete;
  Memory(Memory &&memory) = default;
  Memory &operator=(const Memory &memory) = delete;
  Memory &operator=(Memory &&memory) = delete;

  unsigned char *address;
  size_t size;
  bool is_used;

  static Memory make_memory(size_t size) { return Memory(size); }
};
} // namespace static_containers
