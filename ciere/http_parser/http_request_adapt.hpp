/**
 *   \file http_request_adapt.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief adapts a omd::http:request::message to a fusion sequence
 *
 */

#ifndef OMD_HTTP_REQUEST_ADAPT_HPP
#define OMD_HTTP_REQUEST_ADAPT_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include "http_request.hpp"


BOOST_FUSION_ADAPT_STRUCT(
   omd::http::request::request_line_t,
   (omd::http::request::method_t,  method)
   (std::string, uri)
   (std::string, version)
)


BOOST_FUSION_ADAPT_STRUCT(
   omd::http::request::message,
   (omd::http::request::request_line_t,  request)
   (omd::http::request::message::headers_t, headers)
)


#endif  // OMD_HTTP_REQUEST_HPP
