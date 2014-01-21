/**
 *   \file uri_encoded_data_grammar.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief grammar for parsing uri type encoded data
 *
 *   Grammar will parse data in the format:
 *
 *         value=data&value2=data2
 *
 *   Where value and data are uri (percent) encoded
 *
 */

#ifndef OMD_HTTP_URI_ENCODED_DATA_GRAMMAR_HPP
#define OMD_HTTP_URI_ENCODED_DATA_GRAMMAR_HPP

// --------- for testing --------
// #define BOOST_SPIRIT_DEBUG
// #include <iostream>
// ------------------------------

#include <string>
#include <map>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace omd{ namespace http{ namespace detail{

   namespace qi      = boost::spirit::qi;
   namespace ascii   = boost::spirit::ascii;

   using qi::lit;
   using ascii::char_;

   template <typename Iterator >
   struct uri_encoded_data_grammar : qi::grammar< Iterator, std::map<std::string,std::string>() >
   {
      uri_encoded_data_grammar() : uri_encoded_data_grammar::base_type( start )
      {
         start = query_pair % '&';

         query_pair = url_encoded_string >> '=' >> url_encoded_string;

         url_encoded_string = +( ('%' >> encoded_hex)
                                 |
                                 ~char_( "=&" )
                                 );
      }

      qi::rule< Iterator, std::map<std::string,std::string>() > start;
      qi::rule< Iterator, std::pair<std::string,std::string>() > query_pair;
      qi::rule< Iterator, std::string() > url_encoded_string;
      qi::uint_parser< char, 16, 2, 2 > encoded_hex;
   };
   

}}}


#endif  // OMD_HTTP_URI_ENCODED_DATA_GRAMMAR_HPP
