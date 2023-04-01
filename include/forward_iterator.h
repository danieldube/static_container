#pragma once

#include <cstdlib>
#include <iterator>

namespace static_containers {

template <typename Container>
class ForwardIterator {
 public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type = int64_t;
  using value_type = typename Container::value_type;
  using pointer = value_type*;
  using reference = value_type&;

  reference operator*() const { return referenced_container[element]; }
  pointer operator->() { return &referenced_container[element]; }

  ForwardIterator& operator++() {
    ++element;
    if (element >= referenced_container.size())
      is_end = true;
    return *this;
  }

  ForwardIterator operator++(int) {
    ForwardIterator temporary = *this;
    ++(*this);
    return temporary;
  }

  friend bool operator==(const ForwardIterator& first,
                         const ForwardIterator& second) {
    if (&first.referenced_container != &second.referenced_container)
      return false;
    if (first.is_end and second.is_end)
      return true;
    if (first.is_end or second.is_end)
      return false;
    if (first.element == second.element)
      return true;
    return false;
  }

  friend bool operator!=(const ForwardIterator& first,
                         const ForwardIterator& second) {
    return not(first == second);  // NOLINT
  };

  static ForwardIterator make_iterator(Container& container) {
    return ForwardIterator(container, false);
  }

  static ForwardIterator make_end_iterator(Container& container) {
    return ForwardIterator(container, true);
  }

 private:
  explicit ForwardIterator(Container& container, bool is_end = false)
      : referenced_container(container), is_end(is_end) {}

  Container& referenced_container;
  size_t element{0};
  bool is_end{false};
};

}  // namespace static_containers
