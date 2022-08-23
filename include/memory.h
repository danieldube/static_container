#pragma once

namespace static_containers {

class Memory {
  Memory(unsigned char* address, size_t size) :
    address(address),
    size(size)
  {
  }

  unsigned char* address;
  size_t size;

 public:
  static Memory create_memory(size_t size)
  {
    auto memory = new unsigned char[size];
    return Memory(memory, size);
  }
};
}