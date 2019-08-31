#include "CppSip/message/address.h"
#include "CppSip/message/method.h"

#include <iosfwd>

namespace CppSip
{
namespace Message
{


std::ostream& operator<<( std::ostream& s, Method m );
std::ostream& operator<<( std::ostream& s, const IPv4Address& ip );

}

}  // namespace CppSip
