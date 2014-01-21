/**
 *   \file http_request_grammar_test.cpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   Test harness for the omd::http::request::detail::request_grammar
 */
#include <iostream>
//#include <vector>
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/include/qi.hpp>
//#include <boost/fusion/adapted/std_pair.hpp>

#include "detail/http_request.hpp"
//#include "detail/http_request_adapt.hpp"
#include "detail/http_request_parse_grammar.hpp"
#include "detail/http_request_generate_grammar.hpp"


namespace fusion = boost::fusion;

int main()
{
   {
      std::string input_message;
      input_message  = "POST /foo/bar HTTP/1.1\x0d\x0a";
      input_message += "Content-Length: 27\x0d\x0a";
      input_message += "Content-Type: application/x-www-form-urlencoded\x0d\x0a";
      input_message += "Host: www.foo.com\x0d\x0a";
      input_message += "User-Agent: Mozilla/4.0\x0d\x0a";
      input_message += "\x0d\x0a";
      input_message += "userid=joe&password=guessme";

      std::string::const_iterator begin = input_message.begin();
      std::string::const_iterator end   = input_message.end();

      omd::http::request::detail::parse_grammar< std::string::const_iterator > grammar;

      omd::http::request::message msg;

      bool parse_result =  boost::spirit::qi::parse( begin, end, 
						     grammar,
						     msg  ); 

      BOOST_TEST( parse_result == true );
      BOOST_TEST( msg.request.method  == omd::http::request::REQUEST_POST );
      BOOST_TEST( msg.request.uri  == "/foo/bar" );
      BOOST_TEST( msg.request.version  == "1.1" );
      BOOST_TEST( msg.headers.size()  == 4 );
      BOOST_TEST( msg.headers["Content-Length"] == "27" );
      BOOST_TEST( msg.headers["Content-Type"] == "application/x-www-form-urlencoded" );
      BOOST_TEST( end - begin == 27 );

      std::cout << std::string( begin, end ) << std::endl;


      // -------------- generate back for round trip ------------------
      //
      std::string generated;
      typedef std::back_insert_iterator<std::string> iter_t;
      iter_t sink( generated );

      omd::http::request::detail::generate_grammar< iter_t > gen_grammar;

      bool generate_result = boost::spirit::karma::generate( sink,
                                                             gen_grammar,
                                                             msg );

      // trim the body from the original message
      input_message.erase( input_message.size() - 27 );

      std::cout << "------" << std::endl;
      std::cout << input_message << std::endl;
      std::cout << "------" << std::endl;
      std::cout << generated << std::endl;


      BOOST_TEST( generate_result == true );
      BOOST_TEST( input_message == generated );
   }

   {
      std::string input_message( "GET /load/examples/grid/sheldon.xml?_dc=1270105534681 HTTP/1.1\x0d\x0a"
				 "Accept: */*\x0d\x0a"
				 "Accept-Language: en-us\x0d\x0a"
				 "Referer: http://vm.objectmodelingdesigns.com:8888/load/examples/grid/foo.html\x0d\x0a"
				 "x-requested-with: XMLHttpRequest\x0d\x0a"
				 "UA-CPU: x86\x0d\x0a"
				 "Accept-Encoding: gzip, deflate\x0d\x0a"
				 "User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 3.5.30729; .NET CLR 3.0.30618)\x0d\x0a"
				 "Host: vm.objectmodelingdesigns.com:8888\x0d\x0a"
				 "Connection: Keep-Alive\x0d\x0a"
				 "\x0d\x0a" );

      std::string::const_iterator begin = input_message.begin();
      std::string::const_iterator end   = input_message.end();

      omd::http::request::detail::parse_grammar< std::string::const_iterator > grammar;

      omd::http::request::message msg;

      bool parse_result =  boost::spirit::qi::parse( begin, end, 
						     grammar,
						     msg  ); 

      BOOST_TEST( parse_result == true );
      BOOST_TEST( msg.request.method  == omd::http::request::REQUEST_GET );
      BOOST_TEST( msg.request.uri  == "/load/examples/grid/sheldon.xml?_dc=1270105534681" );
      BOOST_TEST( msg.request.version  == "1.1" );
   }




   return boost::report_errors();
}

