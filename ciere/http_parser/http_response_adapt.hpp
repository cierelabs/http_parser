/**
 *   \file http_response_adapt.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief adapts a omd::http:response::message to a fusion sequence
 *
 */

#ifndef OMD_HTTP_RESPONSE_ADAPT_HPP
#define OMD_HTTP_RESPONSE_ADAPT_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include "http_response.hpp"


BOOST_FUSION_ADAPT_STRUCT(
   omd::http::response::status_line_t,
   (omd::http::response::version_t,  version)
   (int, code)
   (std::string, reason)
)


BOOST_FUSION_ADAPT_STRUCT(
   omd::http::response::message,
   (omd::http::response::status_line_t,  status)
   (omd::http::response::message::headers_t, headers)
)


#endif  // OMD_HTTP_RESPONSE_HPP
