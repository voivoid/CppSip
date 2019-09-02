#pragma once

#include <iostream>
#include <optional>
#include <variant>

namespace std
{

// HERE BE DRAGONS !!!

template <typename... Args>
std::ostream& operator<<( std::ostream& s, const std::variant<Args...>& v )
{
  std::visit( [&s]( const auto& val ) { s << val; }, v );
  return s;
}

template <typename T>
std::ostream& operator<<( std::ostream& s, const std::optional<T>& o )
{
  if ( o )
  {
    s << *o;
  }

  return s;
}

}  // namespace std
