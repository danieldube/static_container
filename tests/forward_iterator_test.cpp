#include "catch2/catch.hpp"
#include "include/forward_iterator.h"
#include <vector>

using namespace static_containers;

TEST_CASE("iterator", "[StaticVector]") {
  std::vector<uint64_t> container;
  container.push_back(1);
  container.push_back(2);

  auto iterator =
      ForwardIterator<std::vector<uint64_t>>::make_iterator(container);
  auto end =
      ForwardIterator<std::vector<uint64_t>>::make_end_iterator(container);
  CHECK(iterator != end);
  CHECK(*iterator == 1);
  CHECK(*(iterator++) == 1);
  CHECK(iterator != end);
  ++iterator;
  CHECK(iterator == end);
}
