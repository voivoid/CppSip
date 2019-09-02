#include "output/sip_message.h"
#include "output/std.h"

#include <iostream>

namespace CppSip
{

namespace Message
{


std::ostream& operator<<( std::ostream& s, Method m )
{
  switch ( m )
  {
    case Method::Ack: s << "ACK"; break;
    case Method::Bye: s << "BYE"; break;
    case Method::Cancel: s << "CANCEL"; break;
    case Method::Invite: s << "INVITE"; break;
    case Method::Options: s << "OPTIONS"; break;
    case Method::Register: s << "REGISTER"; break;
  }

  return s;
}

std::ostream& operator<<( std::ostream& s, const IPv4Address& ip )
{
  s << unsigned( ip.a ) << '.' << unsigned( ip.b ) << '.' << unsigned( ip.c ) << '.' << unsigned( ip.d );
  return s;
}

std::ostream& operator<<( std::ostream& s, const HostPort& hp )
{
  s << hp.host;

  if ( hp.port )
  {
    s << ':' << *hp.port;
  }

  return s;
}

std::ostream& operator<<( std::ostream& s, const SipUri& sip_uri )
{
  s << ( sip_uri.sips ? "sips" : "sip" ) << ':' << sip_uri.host_port;

  return s;
}

}  // namespace Message

}  // namespace CppSip
