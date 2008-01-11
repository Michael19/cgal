// Copyright (c) 2006-2008 Fernando Luis Cacciola Carballal. All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//

// $URL: svn+ssh://CGAL/svn/cgal/trunk/Straight_skeleton_2/include/CGAL/Straight_skeleton_builder_2.h $
// $Id: Straight_skeleton_builder_2.h 40951 2007-11-19 16:33:25Z fcacciola $
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_CREATE_OFFSET_POLYGONS_FROM_POLYGON_WITH_HOLES_2_H
#define CGAL_CREATE_OFFSET_POLYGONS_FROM_POLYGON_WITH_HOLES_2_H

#include <CGAL/Create_offset_polygons_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Arrange_offset_polygons_2.h>

CGAL_BEGIN_NAMESPACE

template<class FT, class OfK, class SsK>
std::vector< boost::shared_ptr< Polygon_2<OfK> > >
inline
create_interior_skeleton_and_offset_polygons_2 ( FT aOffset, Polygon_with_holes_2<OfK> const& aPoly, SsK const& ssk )
{
  OfK ofk ;
  return create_interior_skeleton_and_offset_polygons_2(aOffset
                                                       ,aPoly.outer_boundary()
                                                       ,aPoly.holes_begin()
                                                       ,aPoly.holes_end()
                                                       ,ofk
                                                       ,ssk
                                                       );
    
}

template<class FT, class OfK>
std::vector< boost::shared_ptr< Polygon_2<OfK> > >
inline
create_interior_skeleton_and_offset_polygons_2 ( FT aOffset, Polygon_with_holes_2<OfK> const& aPoly )
{
  return create_interior_skeleton_and_offset_polygons_2(aOffset, aPoly, Exact_predicates_inexact_constructions_kernel() );
}

template<class FT, class OfK>
std::vector< boost::shared_ptr< Polygon_with_holes_2<OfK> > >
inline
create_exterior_skeleton_and_offset_polygons_with_holes_2 ( FT                    aOffset
                                                          , Polygon_2<OfK> const& aPoly
                                                          , bool                  aDontReverseOrientation = false
                                                          )
{
  return arrange_offset_polygons_2(create_exterior_skeleton_and_offset_polygons_with_holes_2(aOffset
                                                                                            ,aPoly
                                                                                            ,aDontReverseOrientation
                                                                                            )
                                  );
}

template<class FT, class OfK, class SsK>
std::vector< boost::shared_ptr< Polygon_with_holes_2<OfK> > >
inline
create_interior_skeleton_and_offset_polygons_with_holes_2 ( FT aOffset, Polygon_with_holes_2<OfK> const& aPoly, SsK const& ssk )
{
  return arrange_offset_polygons_2(create_interior_skeleton_and_offset_polygons_2(aOffset,aPoly,ssk));
}

template<class FT, class OfK>
std::vector< boost::shared_ptr< Polygon_with_holes_2<OfK> > >
inline
create_interior_skeleton_and_offset_polygons_with_holes_2 ( FT aOffset, Polygon_with_holes_2<OfK> const& aPoly )
{
  return arrange_offset_polygons_2(create_interior_skeleton_and_offset_polygons_2(aOffset,aPoly));
}

template<class FT, class OfK, class SsK>
std::vector< boost::shared_ptr< Polygon_with_holes_2<OfK> > >
inline
create_exterior_skeleton_and_offset_polygons_with_holes_2 ( FT                    aOffset
                                                          , Polygon_2<OfK> const& aPoly
                                                          , SsK const&            ssk 
                                                          )
{
  return arrange_offset_polygons_2(create_exterior_skeleton_and_offset_polygons_with_holes_2(aOffset
                                                                                            ,aPoly
                                                                                            ,ssk
                                                                                            )
                                  );
}



CGAL_END_NAMESPACE


#endif 
// EOF //
