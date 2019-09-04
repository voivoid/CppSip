#pragma once

#include "CppSip/message/request/request.h"
#include "CppSip/message/response/response.h"

#include "boost/variant.hpp"

namespace CppSip
{

namespace Message
{

using Message = boost::variant<Request, Response>;

}
}  // namespace CppSip
