/**
 *   \file http_request_util.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief utilities for parsing bits
 *
 */

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include "http_util.hpp"
#include "detail/http_response_grammar.hpp"
#include "detail/http_request_parse_grammar.hpp"
#include "detail/http_uri_grammar.hpp"
#include "detail/uri_encoded_data_grammar.hpp"

namespace omd{ namespace http{

   namespace detail{

      template< typename Iterator >
      bool parse_request( Iterator& begin, Iterator end, omd::http::request::message& msg )
      {
         omd::http::request::detail::parse_grammar< Iterator > grammar;

         return boost::spirit::qi::parse( begin, end, 
                                          grammar,
                                          msg  ); 
      }

      template< typename Iterator >
      bool parse_uri( Iterator& begin, Iterator end, omd::http::request::uri_parts& parts )
      {
         omd::http::request::detail::uri_grammar< Iterator > grammar;

         return boost::spirit::qi::parse( begin, end, 
                                          grammar,
                                          parts  ); 
      }

   }


   bool parse_request( const std::string& input, omd::http::request::message& msg )
   {
      std::string::const_iterator begin = input.begin();
      return detail::parse_request( begin, input.end(), msg );
   }

   bool parse_request( std::string::iterator& begin, std::string::iterator end, 
                       omd::http::request::message& msg )
   {
      return detail::parse_request( begin, end, msg );
   }

   bool parse_request( const char* & begin, const char* end, 
                       omd::http::request::message& msg )
   {
      return detail::parse_request( begin, end, msg );
   }

   bool parse_uri( const std::string& input, omd::http::request::uri_parts& parts )
   {
      std::string::const_iterator begin = input.begin();
      return detail::parse_uri( begin, input.end(), parts );
   }

   bool parse_uri( std::string::iterator& begin, std::string::iterator end,
                   omd::http::request::uri_parts& parts )
   {
      return detail::parse_uri( begin, end, parts );
   }

   bool generate_response( omd::http::response::message& msg, std::string& generated )
   {
      typedef std::back_insert_iterator<std::string> iter_t;
      iter_t sink( generated );

      omd::http::response::detail::response_grammar< iter_t > grammar;
      return boost::spirit::karma::generate( sink, grammar, msg );
   }

   bool form_decode( const char* & begin, const char* end, std::map<std::string,std::string>& value_map )
   {
      omd::http::detail::uri_encoded_data_grammar< const char* > grammar;
      return boost::spirit::qi::parse( begin, end, 
                                       grammar,
                                       value_map  ); 
   }

}}

