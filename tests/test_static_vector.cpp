#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "include/static_vector.h"
#include "include/memory.h"

using namespace static_containers;

TEST_CASE("StaticVector", "[constructor]") {

  StaticVector<double> vector;
}


TEST_CASE("Memory", "[constructor]") {
  Memory::make_memory(1024);
}
