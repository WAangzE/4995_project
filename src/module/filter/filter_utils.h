#progma once

namespace filter_utils {
template <typename Op, typename Element>
concept BinaryOperation = requires(Op op, Element e1, Element e2) {
  { op(e1, e2) }
  ->same_as<Element>;
};

template <typename Container, typename Operation, typename Accumulator>
requires ranges::forward_range<Container>&& same_as<ranges::range_value_t<Container>, Accumulator>&&
    equality_comparable<ranges::iterator_t<Container>>&& copyable<Accumulator>&&
        copy_constructible<Accumulator>&& BinaryOperation<Operation, Accumulator>&&
            sentinel_for<ranges::sentinel_t<Container>, ranges::iterator_t<Container>>
                Accumulator filterAccer(Container c, Operation op, Accumulator acc) {
  for (auto it = c.begin(); it != c.end(); it++) {
    acc = op(acc, *it);
  }
  return acc;
}

}  // namespace filter_utils