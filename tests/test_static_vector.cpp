#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "include/memory.h"
#include "include/static_vector.h"

using namespace static_containers;

TEST_CASE("StaticVector", "[constructor]") { StaticVector<double> vector; }

TEST_CASE("Memory", "[constructor]") { Memory::make_memory(1024); }

TEST_CASE("Memory allocate") {
  auto memory = Memory::make_memory(1024);

  CHECK(memory.is_used == false);
  {
    auto token = memory.allocate();
    CHECK(memory.is_used == true);
  }
  CHECK(memory.is_used == false);

  memory.allocate();
  CHECK(memory.is_used == false);
}
