/**
 *   \file uri_parts_adapt.hpp
 *   Copyright (c) 2010 Object Modeling Designs
 *
 *   \brief 
 *
 */

#ifndef OMD_URI_PARTS_ADAPT_HPP
#define OMD_URI_PARTS_ADAPT_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include "uri_parts.hpp"


BOOST_FUSION_ADAPT_STRUCT(
   omd::http::request::uri_parts,
   (boost::optional<std::string>, root)
   (boost::optional<std::string>, hierarchy)
   (boost::optional< omd::http::request::uri_parts::query_t >, queries)
)


#endif  // OMD_URI_PARTS_ADAPRT_HPP

