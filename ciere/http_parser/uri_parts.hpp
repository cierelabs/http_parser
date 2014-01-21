/**
 *   \file uri_parts.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief 
 *
 */

#ifndef OMD_URI_PARTS_HPP
#define OMD_URI_PARTS_HPP

#include <map>
#include <string>
#include <boost/optional.hpp>

namespace omd{ namespace http{ namespace request{

   struct uri_parts
   {
         typedef std::map< std::string, std::string > query_t;
         boost::optional< std::string > root;
         boost::optional< std::string > hierarchy;
         boost::optional< query_t > queries;
   };

}}}


#endif  // OMD_URI_PARTS_HPP

