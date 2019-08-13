#include "boost/test/unit_test.hpp"

#include "CppSip/parser/message_parser.h"
#include "test_utils/message.h"

#include "boost/spirit/home/x3.hpp"

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

CppSip::Method parse_method(const std::string_view input) {
  return parse<CppSip::Method>(CppSip::Parsers::method, input);
}

CppSip::SipVersion parse_sip_version(const std::string_view input) {
  return parse<CppSip::SipVersion>(CppSip::Parsers::sip_version, input);
}

} // namespace

BOOST_AUTO_TEST_SUITE(parser)

BOOST_AUTO_TEST_CASE(test_method_parser) {
  BOOST_CHECK(CppSip::Method::Ack == parse_method("ACK"));
  BOOST_CHECK(CppSip::Method::Bye == parse_method("BYE"));
  BOOST_CHECK(CppSip::Method::Cancel == parse_method("CANCEL"));
  BOOST_CHECK(CppSip::Method::Invite == parse_method("INVITE"));
  BOOST_CHECK(CppSip::Method::Options == parse_method("OPTIONS"));
  BOOST_CHECK(CppSip::Method::Register == parse_method("REGISTER"));
}

BOOST_AUTO_TEST_CASE(test_method_parser_fail) {
  BOOST_CHECK_THROW(parse_method("UNKNOWN"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_sip_version_parser) {
  {
    const auto [major, minor] = parse_sip_version("SIP/1.0");
    BOOST_CHECK_EQUAL(major, 1);
    BOOST_CHECK_EQUAL(minor, 0);
  }

  {
    const auto [major, minor] = parse_sip_version("SIP/2.1");
    BOOST_CHECK_EQUAL(major, 2);
    BOOST_CHECK_EQUAL(minor, 1);
  }
}

BOOST_AUTO_TEST_CASE(test_sip_version_parser_fail) {
  BOOST_CHECK_THROW(parse_sip_version("SIP/2"), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
