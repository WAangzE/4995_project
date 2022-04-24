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

template <typename Container, typename Operation, typename Accumulator, typename P>
requires std::predicate<P, std::iter_value_t<ranges::iterator_t<Container>>>&&
    ranges::forward_range<Container>&& same_as<ranges::range_value_t<Container>, Accumulator>&&
        equality_comparable<ranges::iterator_t<Container>>&& copyable<Accumulator>&&
            copy_constructible<Accumulator>&& BinaryOperation<Operation, Accumulator>&&
                sentinel_for<ranges::sentinel_t<Container>, ranges::iterator_t<Container>>
                    Accumulator filterAccerConditional(Container c, Operation op, Accumulator acc, P f) {
  for (auto it = c.begin(); it != c.end(); it++) {
    if(f(*it))
        acc = op(acc, *it);
  }
  return acc;
}

}  // namespace filter_utils