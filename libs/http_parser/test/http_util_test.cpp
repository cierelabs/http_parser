/**
 *   \file http_request_util_test.cpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   Test harness for the omd::http::request utilities
 */

#include <iostream>
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/include/qi.hpp>

#include "http_response.hpp"
#include "http_request.hpp"
#include "uri_parts.hpp"
#include "http_util.hpp"

int main()
{
   {
      std::string input_message;
      input_message  = "POST /foo/bar HTTP/1.1\x0d\x0a";
      input_message += "Host: www.foo.com\x0d\x0a";
      input_message += "User-Agent: Mozilla/4.0\x0d\x0a";
      input_message += "Content-Length: 27\x0d\x0a";
      input_message += "Content-Type: application/x-www-form-urlencoded\x0d\x0a";
      input_message += "\x0d\x0a";
      input_message += "userid=joe&password=guessme";

      omd::http::request::message msg;

      BOOST_TEST( omd::http::parse_request( input_message, msg ) == true );
      BOOST_TEST( msg.request.method  == omd::http::request::REQUEST_POST );
      BOOST_TEST( msg.request.uri  == "/foo/bar" );
      BOOST_TEST( msg.request.version  == "1.1" );
      BOOST_TEST( msg.headers.size()  == 4 );
      BOOST_TEST( msg.headers["Content-Length"] == "27" );
      BOOST_TEST( msg.headers["Content-Type"] == "application/x-www-form-urlencoded" );
   }

   {
      std::string uri_string( "/my_command/some/big/path?query1=foo&query2=bar&query3=gorp" );

      omd::http::request::uri_parts parts;

      BOOST_TEST( omd::http::parse_uri( uri_string, parts ) == true );
      BOOST_TEST( *parts.root       == "my_command" );
      BOOST_TEST( *parts.hierarchy  == "some/big/path" );
      BOOST_TEST( (*parts.queries)[ "query1" ]  == "foo" );
      BOOST_TEST( (*parts.queries)[ "query2" ]  == "bar" );
      BOOST_TEST( (*parts.queries)[ "query3" ]  == "gorp" );
   }

   {
     omd::http::response::message msg;
     msg.status.version = omd::http::response::HTTP_1_1;
     msg.status.code    = 200;
     msg.status.reason  = "OK";
     msg.headers["Content-Length"] = "27";
     msg.headers["Content-Type"] =   "application/x-www-form-urlencoded";

     std::string generated;
     std::string generated_compare( "HTTP/1.1 200 OK\x0d\x0a"
				    "Content-Length: 27\x0d\x0a"
				    "Content-Type: application/x-www-form-urlencoded\x0d\x0a"
				    "\x0d\x0a" );
				 
     BOOST_TEST( omd::http::generate_response( msg, generated ) == true );
     BOOST_TEST( generated == generated_compare );
   }

   return boost::report_errors();
}


