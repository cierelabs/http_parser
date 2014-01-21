/**
 *   \file http_response_grammar.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief grammar for generating http response
 *
 *   Based loosely on http://tools.ietf.org/html/rfc2616
 *
 */

#ifndef OMD_HTTP_RESPONSE_GRAMMAR_HPP
#define OMD_HTTP_RESPONSE_GRAMMAR_HPP


#include <string>
#include <map>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/sequence.hpp>
//#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>


// current hack. The grammar works on http_response objects.
// need to make this generic
#include "http_response.hpp"
#include "detail/http_response_adapt.hpp"


namespace omd{ namespace http{ namespace response{ namespace detail{

   namespace phoenix = boost::phoenix;
   namespace karma   = boost::spirit::karma;
   namespace ascii   = boost::spirit::ascii;
   namespace fusion  = boost::fusion;

   using karma::lit;
   using karma::int_;
   using ascii::char_;
   using ascii::string;

   struct version_symbol_ : karma::symbols< omd::http::response::version_t, char const* >
   {
         version_symbol_()
         {
            add
               ( omd::http::response::HTTP_1_0, "HTTP/1.0" )
               ( omd::http::response::HTTP_1_1, "HTTP/1.1" )
               ;
         }

   } version_symbol;


   template <typename Iterator >
   struct response_grammar : karma::grammar< Iterator, omd::http::response::message() >
   {
         response_grammar()
            : response_grammar::base_type( message )
         {
            message =
                  status_line
               << *header_pair
               << crlf
               ;

            status_line = version_symbol << ' ' << int_ << ' ' << *char_  << crlf;

            header_pair = string << ": " << string << crlf ;

            crlf = "\x0d\x0a";
         }

         karma::rule< Iterator, omd::http::response::message() > message;
         karma::rule< Iterator, omd::http::response::status_line_t() > status_line;
         karma::rule< Iterator, omd::http::response::message::headers_t::value_type() > header_pair;
         karma::rule< Iterator > crlf;
   };

}}}}


#endif  // OMD_HTTP_RESPONSE_GRAMMAR_HPP
