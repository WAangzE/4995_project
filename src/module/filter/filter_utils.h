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
    if (f(*it))
      acc = op(acc, *it);
  }
  return acc;
}

template <typename Mapper, typename Element, typename OutputT>
concept isMapper = requires(Mapper mapper, Element e1) {
  { mapper(e1) }
  ->same_as<OutputT>;
};

template <typename Container>
concept validMappingContainer =
    ranges::forward_range<Container>&& equality_comparable<ranges::iterator_t<Container>>&&
        copyable<ranges::range_value_t<Container>>&& copy_constructible<ranges::iterator_t<Container>>&&
            sentinel_for<ranges::sentinel_t<Container>, ranges::iterator_t<Container>>;

template <typename InContainer, typename Mapper, typename OutContainer>
requires isMapper<Mapper, ranges::range_value_t<InContainer>, ranges::range_value_t<OutContainer>>&&
    validMappingContainer<InContainer>&& validMappingContainer<OutContainer> void
    filterMapper(InContainer cIn, Mapper mapper, OutContainer cOut) {
  auto itO = cOut.begin();
  for (auto itI = cIn.begin(); itI != cIn.end(); itI++, itO++) {
    *itO = mapper(*itI);
  }
}

template <typename InContainer, typename Mapper, typename OutContainer, typename P>
requires std::predicate<P, std::iter_value_t<ranges::iterator_t<InContainer>>>&&
    isMapper<Mapper, ranges::range_value_t<InContainer>, ranges::range_value_t<OutContainer>>&&
        validMappingContainer<InContainer>&& validMappingContainer<OutContainer> int
        filterMapperConditionalIn(InContainer cIn, Mapper mapper, OutContainer cOut, P f) {
  int counter{0};
  auto itO = cOut.begin();
  for (auto itI = cIn.begin(); itI != cIn.end(); itI++) {
    if (f(*itI)) {
      *itO = mapper(*itI);
      itO++;
      counter++;
    }
  }
  return counter;
}

template <typename InContainer, typename Mapper, typename OutContainer, typename P>
requires std::predicate<P, std::iter_value_t<ranges::iterator_t<OutContainer>>>&&
    isMapper<Mapper, ranges::range_value_t<InContainer>, ranges::range_value_t<OutContainer>>&&
        validMappingContainer<InContainer>&& validMappingContainer<OutContainer> int
        filterMapperConditionalOut(InContainer cIn, Mapper mapper, OutContainer cOut, P f) {
  int counter{0};
  auto itO = cOut.begin();
  for (auto itI = cIn.begin(); itI != cIn.end(); itI++) {
    auto out = mapper(*itI);
    if (f(out)) {
      *itO = out;
      itO++;
      counter++;
    }
  }
  return counter;
}

template <typename Container>
concept validFilteringContainer =
    ranges::forward_range<Container>&& equality_comparable<ranges::iterator_t<Container>>&&
        copyable<ranges::range_value_t<Container>>&& copy_constructible<ranges::iterator_t<Container>>&&
            sentinel_for<ranges::sentinel_t<Container>, ranges::iterator_t<Container>>;

template <typename Container, typename P>
requires validFilteringContainer<Container> int filterBasic(Container c, P f) {
  int counter{0};
  auto cur = c.begin();
  for (auto it = c.begin(); it != c.end(); it++) {
    auto tmp = *it;
    if (f(tmp)) {
      *cur = tmp;
      cur++;
      counter++;
    }
  }
  return counter
}

}  // namespace filter_utils