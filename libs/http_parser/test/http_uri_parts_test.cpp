/**
 *   \file http_uri_parts_test.cpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   Test harness for the omd::http::request::uri_parts
 */
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/sequence.hpp>
#include "detail/uri_parts.hpp"
#include "detail/uri_parts_adapt.hpp"

namespace fusion = boost::fusion;

int main()
{
   omd::http::request::uri_parts parts;
   
   // verify the fusion adaption
   fusion::at_c<0>( parts ) = "some_command";
   fusion::at_c<1>( parts ) = "my/favorite/path";
//   fusion::at_c<2>( parts )[ "foo" ] = "bar";

   // check the results
   BOOST_TEST( *parts.root     == "some_command" ); 
   BOOST_TEST( *parts.hierarchy == "my/favorite/path" ); 

//    BOOST_TEST( parts.queries.size()   == 1 );
//    BOOST_TEST( parts.queries[ "foo" ] == "bar" );
   
   return boost::report_errors();
}

