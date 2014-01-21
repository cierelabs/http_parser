/**
 *   \file http_request_util.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief utilities for parsing bits
 *
 */

#ifndef OMD_HTTP_REQUEST_UTIL_HPP
#define OMD_HTTP_REQUEST_UTIL_HPP

#include <string>
#include <map>

namespace omd{ namespace http{

   namespace request{
      struct message;
      struct uri_parts;
   }

   namespace response{
      struct message;
   }
   
   bool parse_request( const std::string& input, omd::http::request::message& msg );
   bool parse_request( std::string::iterator& begin, std::string::iterator end, omd::http::request::message& msg );
   bool parse_request( const char* & begin, const char* end, omd::http::request::message& msg );
   bool parse_uri( const std::string& input, omd::http::request::uri_parts& parts );
   bool parse_uri( std::string::iterator& begin, std::string::iterator end, omd::http::request::uri_parts& parts );
   bool generate_response( omd::http::response::message& msg, std::string& generated );

//   void encode( std::map<std::string,std::string>& value_map );
   bool form_decode( const char* & begin, const char* end, std::map<std::string,std::string>& value_map );
}}

#endif  // OMD_HTTP_REQUEST_UTIL_HPP
