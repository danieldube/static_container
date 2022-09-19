#ifndef BUILD_TESTS_INSTANCE_COUNTER_H_
#define BUILD_TESTS_INSTANCE_COUNTER_H_
#include <cstdlib>
#include <iostream>

class InstanceCounter {
public:
  InstanceCounter() {
    ++instances();
    std::cout << "constructor" << std::endl;
  }
  ~InstanceCounter() {
    --instances();
    std::cout << "destructor" << std::endl;
  }
  InstanceCounter(InstanceCounter &&) noexcept {
    ++instances();
    std::cout << "rvalue copy" << std::endl;
  };
  InstanceCounter &operator=(InstanceCounter &&) noexcept {
    std::cout << "rvalue assignment" << std::endl;
    return *this;
  };

  static void reset() {
    instances() = 0;
    std::cout << "reset" << std::endl;
  }

  static std::size_t &instances() {
    static std::size_t instances(0);
    return instances;
  }
};

#endif // BUILD_TESTS_INSTANCE_COUNTER_H_
