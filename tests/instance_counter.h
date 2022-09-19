#ifndef BUILD_TESTS_INSTANCE_COUNTER_H_
#define BUILD_TESTS_INSTANCE_COUNTER_H_
#include <cstdlib>

class InstanceCounter {
public:
  InstanceCounter() { ++instances(); }

  ~InstanceCounter() { --instances(); }

  InstanceCounter(InstanceCounter &&) noexcept { ++instances(); };

  InstanceCounter &operator=(InstanceCounter &&) noexcept {
    instances();
    return *this;
  };

  static std::size_t &instances() {
    static std::size_t instances(0);
    return instances;
  }
};

#endif // BUILD_TESTS_INSTANCE_COUNTER_H_
