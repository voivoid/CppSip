#pragma once

#include "CppSip/message/headers/callid.h"
#include "CppSip/message/headers/content_length.h"
#include "CppSip/message/headers/content_type.h"
#include "CppSip/message/headers/cseq.h"
#include "CppSip/message/headers/max_forwards.h"

#include "boost/variant.hpp"

namespace CppSip
{
namespace Message
{

using Header = boost::variant<Headers::CallId, Headers::ContentLength, Headers::ContentType, Headers::CSeq, Headers::MaxForwards>;

}
}  // namespace CppSip
