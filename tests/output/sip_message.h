#include "CppSip/message/request/request.h"

#include <iosfwd>

namespace CppSip
{
namespace Message
{


std::ostream& operator<<( std::ostream& s, Method m );
std::ostream& operator<<( std::ostream& s, const IPv4Address& ip );
std::ostream& operator<<( std::ostream& s, const HostPort& hp );
std::ostream& operator<<( std::ostream& s, const SipUri& sip_uri );

}  // namespace Message

}  // namespace CppSip
