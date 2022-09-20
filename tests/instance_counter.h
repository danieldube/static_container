#ifndef BUILD_TESTS_INSTANCE_COUNTER_H_
#define BUILD_TESTS_INSTANCE_COUNTER_H_
#include <cstdlib>

class InstanceCounter {
public:
  InstanceCounter() noexcept { ++instances(); }

  ~InstanceCounter() noexcept { --instances(); }

  InstanceCounter(const InstanceCounter &) noexcept { ++instances(); }

  InstanceCounter(InstanceCounter &&) noexcept { ++instances(); };

  InstanceCounter &operator=(const InstanceCounter &) = default;
  InstanceCounter &operator=(InstanceCounter &&) = default;

  static void reset() noexcept { instances() = 0; }

  static std::size_t &instances() noexcept {
    static std::size_t instances(0);
    return instances;
  }
};

#endif // BUILD_TESTS_INSTANCE_COUNTER_H_
