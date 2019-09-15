#pragma once

#include "CppSip/message/headers/headers.h"

#include "CppSip/parser/headers/call_id.h"
#include "CppSip/parser/headers/content_length.h"
#include "CppSip/parser/headers/content_type.h"
#include "CppSip/parser/headers/cseq.h"
#include "CppSip/parser/headers/from_to.h"
#include "CppSip/parser/headers/max_forwards.h"
#include "CppSip/parser/headers/via.h"

#include "boost/spirit/home/x3.hpp"

namespace CppSip
{
namespace Parsers
{

/* message-header = (Accept / Accept-Encoding / Accept-Language / Alert-Info / Allow / Authentication-Info / Authorization / Call-ID /
 Call-Info / Contact / Content-Disposition / Content-Encoding / Content-Language / Content-Length / Content-Type / CSeq / Date / Error-Info
 / Expires / From / In-Reply-To / Max-Forwards / MIME-Version / Min-Expires / Organization / Priority / Proxy-Authenticate /
 Proxy-Authorization / Proxy-Require / Record-Route / Reply-To / Require / Retry-After / Route / Server / Subject /
 Supported / Timestamp / To / Unsupported / User-Agent / Via / Warning / WWW-Authenticate / extension-header) CRLF (!!!) */
inline const auto message_header = bsx3::rule<struct _msg_header, CppSip::Message::Header>{} =
    ( Call_ID | Content_Length | Content_Type | CSeq | From | Max_Forwards | To | Via ) > CRLF;


}  // namespace Parsers
}  // namespace CppSip
