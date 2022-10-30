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

TEST_CASE("move assignment", "[StaticVector]") {
  auto memory = Memory::make_memory(1024);
  StaticVector<uint64_t> source(memory);
  source.push_back(42);
  StaticVector<uint64_t> destination(std::move(source));
  CHECK(destination.capacity() == 128);
  CHECK(destination.size() == 1);
  CHECK(destination[0] == 42);
}

TEST_CASE("range based for", "[StaticVector]") {
  auto memory = Memory::make_memory(1024);
  StaticVector<uint64_t> vector(memory);
  vector.push_back(1);
  vector.push_back(2);
  vector.push_back(3);

  std::vector<uint64_t> results;

  for (auto &element : vector) {
    results.push_back(element);
  }
  CHECK(results[0] == 1);
  CHECK(results[1] == 2);
  CHECK(results[2] == 3);
}
