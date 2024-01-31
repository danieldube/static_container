#include "include/forward_iterator.h"
#include <vector>
#include "catch2/catch.hpp"

using namespace static_containers;

TEST_CASE("iterator", "[StaticVector]") {
  using Container = std::vector<uint64_t>;
  Container container;
  container.push_back(1);
  container.push_back(2);

  using Iterator = ForwardIterator<Container>;
  auto iterator = Iterator::make_iterator(container);
  auto end = Iterator::make_end_iterator(container);
  CHECK(iterator != end);
  CHECK(*iterator == 1);
  CHECK(*(iterator++) == 1);
  CHECK(iterator != end);
  ++iterator;
  CHECK(iterator == end);
}

TEST_CASE("std_fill_iterator", "[StaticVector]") {
  using Container = std::vector<uint64_t>;
  Container container;
  container.push_back(1);
  container.push_back(2);
  container.push_back(3);

  using Iterator = ForwardIterator<Container>;
  std::fill(Iterator::make_iterator(container),
            Iterator::make_end_iterator(container), 42);

  for (const auto element : container)
    CHECK(element == 42);
}
