/**
 *   \file http_request_message_test.cpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   Test harness for the omd::http::request::message
 */
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/sequence.hpp>
#include "detail/http_request.hpp"
#include "detail/http_request_adapt.hpp"

namespace fusion = boost::fusion;

int main()
{
   omd::http::request::message msg;
   
   // verify the fusion adaption
   fusion::at_c<0>( fusion::at_c<0>(msg) ) = omd::http::request::REQUEST_POST;
   fusion::at_c<1>( fusion::at_c<0>(msg) ) = "/my/favorite/path";
   fusion::at_c<2>( fusion::at_c<0>(msg) ) = "1.1";
   fusion::at_c< 1 >( msg )[ "Header1" ] = "value1";
   fusion::at_c< 1 >( msg )[ "Header2" ] = "value2";


   // check the results

   BOOST_TEST( msg.request.method   == omd::http::request::REQUEST_POST );
   BOOST_TEST( msg.request.uri      == "/my/favorite/path" );
   BOOST_TEST( msg.request.version  == "1.1" );

   BOOST_TEST( msg.headers.size()  == 2 );
   BOOST_TEST( msg.headers[ "Header1" ] == "value1" );
   BOOST_TEST( msg.headers[ "Header2" ] == "value2" );
   
   return boost::report_errors();
}

