/**
 *   \file http_response.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief http response message
 *
 */

#ifndef OMD_HTTP_RESPONSE_HPP
#define OMD_HTTP_RESPONSE_HPP

#include <map>
#include <string>


namespace omd{ namespace http{ namespace response{

enum version_t
{
   HTTP_1_0, HTTP_1_1
};

struct status_line_t
{
      version_t    version;
      int          code;
      std::string  reason;
};

struct message
{
      typedef std::map< std::string, std::string > headers_t;

      status_line_t  status;
      headers_t      headers;
};


}}}


#endif  // OMD_HTTP_RESPONSE_HPP
