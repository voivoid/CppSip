#include "CppSip/message/address.h"

#include <tuple>

namespace
{
auto tie_ipaddr( const CppSip::Message::IPv4Address& ip )
{
  return std::tie( ip.a, ip.b, ip.c, ip.d );
}
}  // namespace

namespace CppSip
{

namespace Message
{


bool operator==( const IPv4Address& ip1, const IPv4Address& ip2 )
{
  return tie_ipaddr( ip1 ) == tie_ipaddr( ip2 );
}

bool operator<( const IPv4Address& ip1, const IPv4Address& ip2 )
{
  return tie_ipaddr( ip1 ) < tie_ipaddr( ip2 );
}

}  // namespace Message

}  // namespace CppSip
