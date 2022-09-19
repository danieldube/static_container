#include "catch2/catch.hpp"
#include <instance_counter.h>

TEST_CASE("test counter", "[InstanceCounter]") {
  InstanceCounter::reset();
  CHECK(InstanceCounter::instances() == 0);
  {
    auto counter = InstanceCounter();
    CHECK(InstanceCounter::instances() == 1);
  }
  CHECK(InstanceCounter::instances() == 0);
  {
    InstanceCounter counter_1;
    InstanceCounter counter_2(std::move(counter_1));
    CHECK(InstanceCounter::instances() == 2);
    auto counter_3 = InstanceCounter();
    counter_2 = std::move(counter_3);
    CHECK(InstanceCounter::instances() == 3);
  }
  CHECK(InstanceCounter::instances() == 0);
}
