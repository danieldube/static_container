#include "catch2/catch.hpp"
#include <instance_counter.h>

TEST_CASE("test counter", "[InstanceCounter]") {
  CHECK(InstanceCounter::instances() == 0);
  {
    auto counter = InstanceCounter();
    CHECK(InstanceCounter::instances() == 1);
  }
  CHECK(InstanceCounter::instances() == 0);
  {
    auto counter_1 = InstanceCounter();
    InstanceCounter counter_2(std::move(counter_1));
    CHECK(InstanceCounter::instances() == 2);
  }
  CHECK(InstanceCounter::instances() == 0);
}
