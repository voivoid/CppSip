#pragma once

#include <variant>

template <typename Variant, typename T>
bool check_variant_is( const Variant& variant, const T& expected )
{
  auto val = std::get_if<T>( &variant );
  if ( !val )
  {
    return false;
  }

  return expected == *val;
}
