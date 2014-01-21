/**
 *   \file http_response_grammar_test.cpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   Test harness for the omd::http::response::detail::response_grammar
 */
#include <iostream>
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/include/karma.hpp>
#include "detail/http_response.hpp"
#include "detail/http_response_grammar.hpp"


namespace fusion = boost::fusion;

int main()
{
   omd::http::response::message msg;
   msg.status.version = omd::http::response::HTTP_1_1;
   msg.status.code    = 200;
   msg.status.reason  = "OK";
   msg.headers["Content-Length"] = "27";
   msg.headers["Content-Type"] =   "application/x-www-form-urlencoded";

   std::string generated;
   typedef std::back_insert_iterator<std::string> iter_t;
   iter_t sink( generated );

   omd::http::response::detail::response_grammar< iter_t > grammar;

   bool generate_result = boost::spirit::karma::generate( sink,
							  grammar,
							  msg );

   std::string generated_compare( "HTTP/1.1 200 OK\x0d\x0a"
				  "Content-Length: 27\x0d\x0a"
				  "Content-Type: application/x-www-form-urlencoded\x0d\x0a"
				  "\x0d\x0a" );
				 
   BOOST_TEST( generate_result == true );
   BOOST_TEST( generated == generated_compare );

   return boost::report_errors();
}

