/**
 *   \file http_request.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief http request message
 *
 */

#ifndef OMD_HTTP_REQUEST_HPP
#define OMD_HTTP_REQUEST_HPP

#include <map>
#include <string>


namespace omd{ namespace http{ namespace request{

enum method_t
{
   REQUEST_OPTIONS, 
   REQUEST_GET, 
   REQUEST_HEAD, 
   REQUEST_POST, 
   REQUEST_PUT, 
   REQUEST_DELETE, 
   REQUEST_TRACE, 
   REQUEST_CONNECT
};

struct request_line_t
{
      method_t    method;
      std::string uri;
      std::string version;
};

struct message
{
      typedef std::map< std::string, std::string > headers_t;

      request_line_t request;
      headers_t      headers;
};


}}}


#endif  // OMD_HTTP_REQUEST_HPP
