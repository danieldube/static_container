#include "catch2/catch.hpp"
#include "include/memory.h"

using namespace static_containers;

TEST_CASE("make memory", "[Memory]") { Memory::make_memory(1024); }

TEST_CASE("allocate memory", "[Memory]") {
  auto memory = Memory::make_memory(1024);

  CHECK(memory.is_used == false);
  {
    auto token = memory.allocate();
    CHECK(memory.is_used == true);
  }
  CHECK(memory.is_used == false);

  memory.allocate();
  CHECK(memory.is_used == false);

  {
    auto token = memory.allocate();
    CHECK_THROWS_AS(memory.allocate(), std::logic_error);
  }
}
