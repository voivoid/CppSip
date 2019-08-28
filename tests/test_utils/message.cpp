#include "test_utils/message.h"

#include <iostream>

namespace CppSip
{

std::ostream& operator<<( std::ostream& s, Method m )
{
  switch ( m )
  {
    case CppSip::Method::Ack: s << "ACK"; break;
    case CppSip::Method::Bye: s << "BYE"; break;
    case CppSip::Method::Cancel: s << "CANCEL"; break;
    case CppSip::Method::Invite: s << "INVITE"; break;
    case CppSip::Method::Options: s << "OPTIONS"; break;
    case CppSip::Method::Register: s << "REGISTER"; break;
  }

  return s;
}

std::ostream& operator<<( std::ostream& s, const IPaddress& ip )
{
  s << unsigned( ip.a ) << '.' << unsigned( ip.b ) << '.' << unsigned( ip.c ) << '.' << unsigned( ip.d );
  return s;
}

}  // namespace CppSip
