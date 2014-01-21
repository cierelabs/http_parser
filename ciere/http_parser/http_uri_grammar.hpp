/**
 *   \file http_uri_grammar.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief grammars and rules for parsing out uri bits
 *
 */

#ifndef OMD_HTTP_URI_GRAMMAR_HPP
#define OMD_HTTP_URI_GRAMMAR_HPP

// --------- for testing --------
// #define BOOST_SPIRIT_DEBUG
// #include <iostream>
// ------------------------------

#include <string>
#include <map>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include "uri_parts.hpp"
#include "detail/uri_parts_adapt.hpp"
#include "detail/uri_encoded_data_grammar.hpp"


namespace omd{ namespace http{ namespace request{ namespace detail{

   namespace qi      = boost::spirit::qi;
   namespace ascii   = boost::spirit::ascii;

   using qi::lit;
   using ascii::char_;

   template <typename Iterator >
   struct uri_grammar : qi::grammar< Iterator, omd::http::request::uri_parts() >
   {
      uri_grammar() : uri_grammar::base_type( start )
      {
         start = 
            lit( '/' )
            >>  -( +( ~char_( "/?" ) ) )
            >>  -( '/' >> +( ~char_( "?" ) ) )
           //            >>  -( '?' >> ( query_pair % '&' ) )
            >>  -( '?' >> uri_encoded_data )
            ;

         //         query_pair = +( ~char_( '=' ) ) >> '=' >> +( ~char_( '&' ) );
//          query_pair = url_encoded_string >> '=' >> url_encoded_string;

//       url_encoded_string = +( ('%' >> encoded_hex)
//                               |
//                               ~char_( "=&" )
//                               );
      }

      qi::rule< Iterator, omd::http::request::uri_parts() > start;
//       qi::rule< Iterator, std::pair<std::string,std::string>() > query_pair;
//       qi::rule< Iterator, std::string() > url_encoded_string;
//       qi::uint_parser< char, 16, 2, 2 > encoded_hex;
      omd::http::detail::uri_encoded_data_grammar< Iterator > uri_encoded_data;
   };
   

}}}}


#endif  // OMD_HTTP_URI_GRAMMAR_HPP
