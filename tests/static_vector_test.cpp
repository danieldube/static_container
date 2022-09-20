#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "include/memory.h"
#include "include/static_vector.h"
#include "instance_counter.h"

using namespace static_containers;

TEST_CASE("constructor", "[StaticVector]") {
  auto memory = Memory::make_memory(1024);
  StaticVector<double> vector(memory);

  CHECK(vector.capacity() == 128);
  vector.push_back(42);
  CHECK(vector[0] == 42);
  vector.push_back(41);
  CHECK(vector[1] == 41);

  CHECK_THROWS_AS(vector[2], std::range_error);
}

TEST_CASE("correct destruction", "[StaticVector]") {
  auto memory = Memory::make_memory(1024);
  {
    StaticVector<InstanceCounter> vector(memory);
    vector.push_back(InstanceCounter());
    CHECK(InstanceCounter::instances() == 1);
  }
  CHECK(InstanceCounter::instances() == 0);
}

TEST_CASE("forward argument", "[StaticVector]") {
  auto memory = Memory::make_memory(1024);
  StaticVector<std::string> vector(memory);
  vector.push_back(std::string());
  const auto string = std::string();
  vector.push_back(string);
  vector.push_back("test");
}

TEST_CASE("make memory", "[Memory]") { Memory::make_memory(1024); }

TEST_CASE("delete double", "[Memory]") {
  auto *pointer = new double(1);
  delete pointer;
}

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
