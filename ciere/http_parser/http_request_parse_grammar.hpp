/**
 *   \file http_request_parse_grammar.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief grammar for parsing http requests
 *
 *   Based loosely on http://tools.ietf.org/html/rfc2616
 *
 */

#ifndef OMD_HTTP_REQUEST_PARSE_GRAMMAR_HPP
#define OMD_HTTP_REQUEST_PARSE_GRAMMAR_HPP

// --------- for testing --------
// #define BOOST_SPIRIT_DEBUG
// #include <iostream>
// ------------------------------

#include <string>
#include <map>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>


// current hack. The grammar works on http_request objects.
// need to make this generic
#include "http_request.hpp"
#include "detail/http_request_adapt.hpp"


namespace omd{ namespace http{ namespace request{ namespace detail{

   namespace phoenix = boost::phoenix;
   namespace spirit  = boost::spirit;
   namespace qi      = boost::spirit::qi;
   namespace ascii   = boost::spirit::ascii;
   namespace fusion  = boost::fusion;

   using namespace qi::labels;
   using qi::lit;
   using qi::lexeme;
   using qi::on_error;
   using qi::raw;
   using spirit::_val;
   using spirit::_1;
   using spirit::int_;
   using spirit::attr;
   using spirit::omit;
   using ascii::alnum;
   using ascii::alpha;
   using ascii::space;
   using ascii::char_;
   using phoenix::construct;
   using phoenix::val;


   /**
    *  symbol table to describe the valid request methods
    */
   struct method_parse_symbol_ : qi::symbols< char, omd::http::request::method_t >
   {
         method_parse_symbol_()
         {
            add
               ( "OPTIONS", omd::http::request::REQUEST_OPTIONS )
               ( "GET",     omd::http::request::REQUEST_GET )
               ( "HEAD",    omd::http::request::REQUEST_HEAD )
               ( "POST",    omd::http::request::REQUEST_POST )
               ( "PUT",     omd::http::request::REQUEST_PUT )
               ( "DELETE",  omd::http::request::REQUEST_DELETE )
               ( "TRACE",   omd::http::request::REQUEST_TRACE )
               ( "CONNECT", omd::http::request::REQUEST_CONNECT )
               ;
         }

   } method_parse_symbol;


   template <typename Iterator >
   struct parse_grammar : qi::grammar< Iterator, omd::http::request::message() >
   {
         parse_grammar()
            : parse_grammar::base_type( message )
         {
            message =
                   request_line
               >>  *header_pair
               >>  crlf
               ;


            request_line =
                   method_parse_symbol >>  ' '
               >>  uri >>  ' '
               >>  http_version
               >>  crlf
               ;

            crlf = lexeme[ lit( '\x0d' ) >> lit( '\x0a' ) ];

            uri = +( ~char_( ' ' ) );

            http_version = lexeme[ "HTTP/" >> raw[ int_ >> '.' >> int_ ] ];

            header_pair = token >> ':' >> lws >> field_value >> crlf ;

            //field_name  = token.alias(); +( ~seperator ); //char_( "A-Z" ) >> *char_( "a-zA-Z_-" );
            field_value  = *( char_ - crlf );
            //field_value = *( alnum | lws );
            
            lws = omit[ -crlf >> *char_( " \x09" ) ] ;

            token = +(~char_( "()<>@,;:\\\"/[]?={} \x09" ));

         }

         qi::rule< Iterator, omd::http::request::message() > message;
         qi::rule< Iterator > crlf;
         qi::rule< Iterator, std::string() > http_version;
         qi::rule< Iterator, std::string() > uri;
         qi::rule< Iterator, std::pair<std::string,std::string>() > header_pair;
         qi::rule< Iterator, omd::http::request::request_line_t() > request_line;
         qi::rule< Iterator, std::string() > field_value;
         qi::rule< Iterator, std::string() > token;
         qi::rule< Iterator > lws;
   };

}}}}


#endif  // HTTP_REQUEST_PARSE_GRAMMAR_HPP
