/**
 *   \file http_uri_grammar_test.cpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   Test harness for the omd::http::request::detail::uri_grammar
 */
#include <iostream>
//#include <vector>
#include <string>
#include <boost/detail/lightweight_test.hpp>
#include <boost/spirit/include/qi.hpp>

#include "uri_parts.hpp"
#include "detail/http_uri_grammar.hpp"


namespace fusion = boost::fusion;

int main()
{
   {
      std::string uri_string( "/my_command/some/big/path?query1=foo&query2=bar&query3=gorp" );
      std::string::const_iterator begin = uri_string.begin();
      std::string::const_iterator end   = uri_string.end();

      omd::http::request::detail::uri_grammar< std::string::const_iterator > grammar;

      omd::http::request::uri_parts parts;

      bool parse_result =  boost::spirit::qi::parse( begin, end, 
						     grammar,
						     parts  ); 

      BOOST_TEST( parse_result == true );
      BOOST_TEST( *parts.root       == "my_command" );
      BOOST_TEST( *parts.hierarchy  == "some/big/path" );
      BOOST_TEST( (*parts.queries)[ "query1" ]  == "foo" );
      BOOST_TEST( (*parts.queries)[ "query2" ]  == "bar" );
      BOOST_TEST( (*parts.queries)[ "query3" ]  == "gorp" );
      BOOST_TEST( end == begin );
   }

   {
      std::string uri_string( "/my_command" );
      std::string::const_iterator begin = uri_string.begin();
      std::string::const_iterator end   = uri_string.end();

      omd::http::request::detail::uri_grammar< std::string::const_iterator > grammar;

      omd::http::request::uri_parts parts;

      bool parse_result =  boost::spirit::qi::parse( begin, end, 
						     grammar,
						     parts  ); 

      BOOST_TEST( parse_result == true );
      BOOST_TEST( *parts.root       == "my_command" );
      BOOST_TEST( !parts.hierarchy );
      BOOST_TEST( !parts.queries );
      BOOST_TEST( end == begin );
   }

   {
      std::string uri_string( "/" );
      std::string::const_iterator begin = uri_string.begin();
      std::string::const_iterator end   = uri_string.end();

      omd::http::request::detail::uri_grammar< std::string::const_iterator > grammar;

      omd::http::request::uri_parts parts;

      bool parse_result =  boost::spirit::qi::parse( begin, end, 
						     grammar,
						     parts  ); 

      BOOST_TEST( parse_result == true );
      BOOST_TEST( !parts.root );
      BOOST_TEST( !parts.hierarchy );
      BOOST_TEST( !parts.queries );
      BOOST_TEST( end == begin );
   }


   {
      std::string uri_string( "/my_command?query1=foo&query2=bar&query3=gorp" );
      std::string::const_iterator begin = uri_string.begin();
      std::string::const_iterator end   = uri_string.end();

      omd::http::request::detail::uri_grammar< std::string::const_iterator > grammar;

      omd::http::request::uri_parts parts;

      bool parse_result =  boost::spirit::qi::parse( begin, end, 
						     grammar,
						     parts  ); 

      BOOST_TEST( parse_result == true );
      BOOST_TEST( *parts.root       == "my_command" );
      BOOST_TEST( !parts.hierarchy );
      BOOST_TEST( (*parts.queries)[ "query1" ]  == "foo" );
      BOOST_TEST( (*parts.queries)[ "query2" ]  == "bar" );
      BOOST_TEST( (*parts.queries)[ "query3" ]  == "gorp" );
      BOOST_TEST( end == begin );
   }

   return boost::report_errors();
}

