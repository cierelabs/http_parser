/**
 *   \file http_request_generate_grammar.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief grammar for generating http requests
 *
 *   Based loosely on http://tools.ietf.org/html/rfc2616
 *
 */

#ifndef OMD_HTTP_REQUEST_GENERATE_GRAMMAR_HPP
#define OMD_HTTP_REQUEST_GENERATE_GRAMMAR_HPP

#include <string>
#include <map>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>


// current hack. The grammar works on http_request objects.
// need to make this generic
#include "http_request.hpp"
#include "detail/http_request_adapt.hpp"


namespace omd{ namespace http{ namespace request{ namespace detail{

   namespace spirit  = boost::spirit;
   namespace karma   = boost::spirit::karma;
   namespace ascii   = boost::spirit::ascii;
   namespace fusion  = boost::fusion;

   using spirit::_val;
   using spirit::_1;
   using spirit::int_;
   using spirit::attr;
   using spirit::omit;
   using ascii::alnum;
   using ascii::alpha;
   using ascii::space;
   using ascii::string;
   using ascii::char_;


   /**
    *  symbol table to describe the valid request methods
    */
   struct method_generate_symbol_ : karma::symbols< omd::http::request::method_t, char const* >
   {
         method_generate_symbol_()
         {
            add
               ( omd::http::request::REQUEST_OPTIONS, "OPTIONS"  )
               ( omd::http::request::REQUEST_GET,     "GET"      )
               ( omd::http::request::REQUEST_HEAD,    "HEAD"     )
               ( omd::http::request::REQUEST_POST,    "POST"     )
               ( omd::http::request::REQUEST_PUT,     "PUT"      )
               ( omd::http::request::REQUEST_DELETE,  "DELETE"   )
               ( omd::http::request::REQUEST_TRACE,   "TRACE"    )
               ( omd::http::request::REQUEST_CONNECT, "CONNECT"  )
               ;
         }

   } method_generate_symbol;


   template <typename Iterator >
   struct generate_grammar : karma::grammar< Iterator, omd::http::request::message() >
   {
      generate_grammar()
         : generate_grammar::base_type( message )
      {
         message =
                request_line
            <<  *header_pair
            <<  crlf
            ;


         request_line =
                method_generate_symbol <<  ' '
            <<  uri <<  ' '
            <<  http_version
            <<  "\x0d\x0a"
            ;

         crlf = "\x0d\x0a";

         uri = string; //+( ~char_( ' ' ) );

         http_version = "HTTP/" << string; //+char_;

         header_pair = token << ": " << field_value << crlf ;

         field_value  = string; //*( char_ - crlf );
            
         token = string; //+(~char_( "()<>@,;:\\\"/[]?={} \x09" ));

      }

      karma::rule< Iterator, omd::http::request::message() > message;
      karma::rule< Iterator > crlf;
      karma::rule< Iterator, std::string() > http_version;
      karma::rule< Iterator, std::string() > uri;
      karma::rule< Iterator, std::pair<std::string,std::string>() > header_pair;
      karma::rule< Iterator, omd::http::request::request_line_t() > request_line;
      karma::rule< Iterator, std::string() > field_value;
      karma::rule< Iterator, std::string() > token;
   };

}}}}


#endif  // HTTP_REQUEST_GENERATE_GRAMMAR_HPP
