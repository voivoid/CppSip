#pragma once

#include "boost/fusion/container/vector.hpp"
#include "boost/spirit/home/x3.hpp"
#include "boost/spirit/include/support_istream_iterator.hpp"

#include <tuple>
#include <utility>

namespace CppSip {

namespace Details {
template <typename T> void assign(T &to, T &&from) { to = std::move(from); }

template <typename... Attrs, size_t... Indices>
void fill_attrs(boost::fusion::vector<Attrs...> &vector, Attrs &... attrs,
                std::index_sequence<Indices...>) {
  (assign(attrs, std::move(boost::fusion::at_c<Indices>(vector))), ...);
}
} // namespace Details

template <typename Iter, typename Parser, typename Skipper, typename Attr>
bool phrase_parse(Iter begin, Iter end, const Parser &parser,
                  const Skipper &skipper, Attr &attr) {
  const bool parsed =
      boost::spirit::x3::phrase_parse(begin, end, parser, skipper, attr);
  return parsed && (begin == end);
}

template <typename Parser, typename Skipper, typename Attr>
bool phrase_parse(std::istream &input, const Parser &parser,
                  const Skipper &skipper, Attr &attr) {
  input >> std::noskipws;
  return phrase_parse(boost::spirit::istream_iterator(input), {}, parser,
                      skipper, attr);
}

template <typename Parser, typename Skipper, typename Attr>
bool phrase_parse(const std::string &line, const Parser &parser,
                  const Skipper &skipper, Attr &attr) {
  return phrase_parse(line.cbegin(), line.cend(), parser, skipper, attr);
}

template <typename Iter, typename Parser, typename Skipper>
bool phrase_parse(Iter begin, Iter end, const Parser &parser,
                  const Skipper &skipper) {
  const bool parsed =
      boost::spirit::x3::phrase_parse(begin, end, parser, skipper);
  return parsed && (begin == end);
}

template <typename Parser, typename Skipper>
bool phrase_parse(std::istream &input, const Parser &parser,
                  const Skipper &skipper) {
  input >> std::noskipws;
  return phrase_parse(boost::spirit::istream_iterator(input), {}, parser,
                      skipper);
}

template <typename Parser, typename Skipper>
bool phrase_parse(const std::string &line, const Parser &parser,
                  const Skipper &skipper) {
  return phrase_parse(line.cbegin(), line.cend(), parser, skipper);
}

template <typename Iter, typename Parser, typename Attr>
bool parse(Iter begin, Iter end, const Parser &parser, Attr &attr) {
  const bool parsed = boost::spirit::x3::parse(begin, end, parser, attr);
  return parsed && (begin == end);
}

template <typename Parser, typename Attr>
bool parse(std::istream &input, const Parser &parser, Attr &attr) {
  input >> std::noskipws;
  return parse(boost::spirit::istream_iterator(input), {}, parser, attr);
}

template <typename Parser, typename Attr>
bool parse(const std::string &line, const Parser &parser, Attr &attr) {
  return parse(line.cbegin(), line.cend(), parser, attr);
}

template <typename Input, typename Parser, typename Skipper, typename... Attrs>
bool phrase_parse_emplace(Input &&input, const Parser &parser,
                          const Skipper &skipper, Attrs &... attrs) {
  boost::fusion::vector<Attrs...> fusion_attrs;
  bool result =
      parse(std::forward<Input>(input), parser, skipper, fusion_attrs);
  if (!result) {
    return false;
  }

  Details::fill_attrs<Attrs...>(fusion_attrs, attrs...,
                                std::index_sequence_for<Attrs...>{});
  return true;
}

} // namespace CppSip
