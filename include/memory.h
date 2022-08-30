#pragma once

#include <cstdlib>
#include <exception>
#include <functional>

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
    Token(std::function<void()> &&deallocation_callback)
        : deallocate(deallocation_callback) {}
    ~Token() { deallocate(); }

  private:
    std::function<void()> deallocate;
  };

  ~Memory() {
    if (address != nullptr)
      free(address);
  }

  Token allocate() {
    is_used = true;
    return Token([this]() { this->deallocate(); });
  }

  static Memory make_memory(size_t size) { return Memory(size); }

  Memory(const Memory &memory) = delete;
  Memory(Memory &&memory) = default;
  Memory &operator=(const Memory &memory) = delete;
  Memory &operator=(Memory &&memory) = delete;

  unsigned char *address;
  size_t size;
  bool is_used;

private:
  void deallocate() { is_used = false; }
};
} // namespace static_containers
