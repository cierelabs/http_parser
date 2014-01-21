/**
 *   \file http_response_message_test.cpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   Test harness for the omd::http::response::message
 */
#include <boost/detail/lightweight_test.hpp>
#include <boost/fusion/sequence.hpp>
#include "detail/http_response.hpp"
#include "detail/http_response_adapt.hpp"

namespace fusion = boost::fusion;

int main()
{
   omd::http::response::message msg;
   
   // verify the fusion adaption
   fusion::at_c<0>( fusion::at_c<0>(msg) ) = omd::http::response::HTTP_1_1;
   fusion::at_c<1>( fusion::at_c<0>(msg) ) = 200;
   fusion::at_c<2>( fusion::at_c<0>(msg) ) = "OK";
   fusion::at_c< 1 >( msg )[ "Header1" ] = "value1";
   fusion::at_c< 1 >( msg )[ "Header2" ] = "value2";


   // check the results
   BOOST_TEST( msg.status.version   == omd::http::response::HTTP_1_1 );
   BOOST_TEST( msg.status.code      == 200 );
   BOOST_TEST( msg.status.reason  == "OK" );

   BOOST_TEST( msg.headers.size()  == 2 );
   BOOST_TEST( msg.headers[ "Header1" ] == "value1" );
   BOOST_TEST( msg.headers[ "Header2" ] == "value2" );
   
   return boost::report_errors();
}

