#include "boost/test/unit_test.hpp"

#include "CppSip/parser/message_parser.h"
#include "test_utils/message.h"

#include "boost/spirit/home/x3.hpp"

#include <string>

namespace {
template <typename Attr, typename Parser>
Attr parse(Parser parser, const std::string_view input) {
  Attr attr;

  const bool parsed =
      boost::spirit::x3::parse(input.begin(), input.end(), parser, attr);
  if (!parsed) {
    throw std::runtime_error("failed to parse");
  }

  return attr;
}

#define define_parser(parser, type)                                            \
  type parse_##parser(const std::string_view input) {                          \
    return parse<type>(CppSip::Parsers::parser, input);                        \
  }

// clang-format off
define_parser(ALPHA, char)
define_parser(DIGIT, char)
define_parser(alphanum, char)
define_parser(domainlabel, std::string)
define_parser(Method, CppSip::Method)
define_parser(SIP_Version, CppSip::SipVersion)
// clang-format on

} // namespace

BOOST_AUTO_TEST_SUITE(parser)

BOOST_AUTO_TEST_CASE(test_ALPHA_parser) {
  BOOST_CHECK_EQUAL('a', parse_ALPHA("a"));
  BOOST_CHECK_EQUAL('s', parse_ALPHA("s"));
  BOOST_CHECK_EQUAL('z', parse_ALPHA("z"));
  BOOST_CHECK_EQUAL('A', parse_ALPHA("A"));
  BOOST_CHECK_EQUAL('S', parse_ALPHA("S"));
  BOOST_CHECK_EQUAL('Z', parse_ALPHA("Z"));

  BOOST_CHECK_THROW(parse_ALPHA("1"), std::runtime_error);
  BOOST_CHECK_THROW(parse_ALPHA("*"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_DIGIT_parser) {
  BOOST_CHECK_EQUAL('0', parse_DIGIT("0"));
  BOOST_CHECK_EQUAL('5', parse_DIGIT("5"));
  BOOST_CHECK_EQUAL('9', parse_DIGIT("9"));

  BOOST_CHECK_THROW(parse_DIGIT("a"), std::runtime_error);
  BOOST_CHECK_THROW(parse_DIGIT("+"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_alphanum_parser) {
  BOOST_CHECK_EQUAL('a', parse_alphanum("a"));
  BOOST_CHECK_EQUAL('s', parse_alphanum("s"));
  BOOST_CHECK_EQUAL('z', parse_alphanum("z"));
  BOOST_CHECK_EQUAL('A', parse_alphanum("A"));
  BOOST_CHECK_EQUAL('S', parse_alphanum("S"));
  BOOST_CHECK_EQUAL('Z', parse_alphanum("Z"));
  BOOST_CHECK_EQUAL('0', parse_alphanum("0"));
  BOOST_CHECK_EQUAL('5', parse_alphanum("5"));
  BOOST_CHECK_EQUAL('9', parse_alphanum("9"));

  BOOST_CHECK_THROW(parse_alphanum("*"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_domainlabel_parser) {
  BOOST_CHECK_EQUAL("X", parse_domainlabel("X"));
  BOOST_CHECK_EQUAL("domain", parse_domainlabel("domain"));
}

BOOST_AUTO_TEST_CASE(test_Method_parser) {
  BOOST_CHECK_EQUAL(CppSip::Method::Ack, parse_Method("ACK"));
  BOOST_CHECK_EQUAL(CppSip::Method::Bye, parse_Method("BYE"));
  BOOST_CHECK_EQUAL(CppSip::Method::Cancel, parse_Method("CANCEL"));
  BOOST_CHECK_EQUAL(CppSip::Method::Invite, parse_Method("INVITE"));
  BOOST_CHECK_EQUAL(CppSip::Method::Options, parse_Method("OPTIONS"));
  BOOST_CHECK_EQUAL(CppSip::Method::Register, parse_Method("REGISTER"));

  BOOST_CHECK_THROW(parse_Method("UNKNOWN"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_SIP_Version_parser) {
  {
    const auto [major, minor] = parse_SIP_Version("SIP/1.0");
    BOOST_CHECK_EQUAL(major, 1);
    BOOST_CHECK_EQUAL(minor, 0);
  }

  {
    const auto [major, minor] = parse_SIP_Version("SIP/2.1");
    BOOST_CHECK_EQUAL(major, 2);
    BOOST_CHECK_EQUAL(minor, 1);
  }

  BOOST_CHECK_THROW(parse_SIP_Version("SIP/2"), std::runtime_error);
  BOOST_CHECK_THROW(parse_SIP_Version("SIP2.1"), std::runtime_error);
  BOOST_CHECK_THROW(parse_SIP_Version("2.1"), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
