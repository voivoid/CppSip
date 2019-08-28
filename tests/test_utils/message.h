#include "CppSip/message/address.h"
#include "CppSip/message/method.h"

#include <iosfwd>

namespace CppSip
{

std::ostream& operator<<( std::ostream& s, Method m );
std::ostream& operator<<( std::ostream& s, const IPaddress& ip );

}  // namespace CppSip
