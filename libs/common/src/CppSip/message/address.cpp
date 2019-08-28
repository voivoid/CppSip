#include "CppSip/message/address.h"

#include <tuple>

namespace
{
auto tie_ipaddr( const CppSip::IPaddress& ip )
{
  return std::tie( ip.a, ip.b, ip.c, ip.d );
}
}  // namespace

namespace CppSip
{

bool operator==( const IPaddress& ip1, const IPaddress& ip2 )
{
  return tie_ipaddr( ip1 ) == tie_ipaddr( ip2 );
}

bool operator<( const IPaddress& ip1, const IPaddress& ip2 )
{
  return tie_ipaddr( ip1 ) < tie_ipaddr( ip2 );
}

}  // namespace CppSip
