#pragma once

#include "CppSip/message/headers/callid.h"
#include "CppSip/message/headers/cseq.h"
#include "CppSip/message/headers/max_forwards.h"

#include <variant>

namespace CppSip
{
namespace Message
{

  using Header = std::variant<Headers::CallId, Headers::CSeq, Headers::MaxForwards>;

}
}