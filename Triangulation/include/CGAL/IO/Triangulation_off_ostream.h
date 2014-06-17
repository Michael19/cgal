// Copyright (c) 2014  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of the License,
// or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL:  $
// $Id:  $
//
// Author(s)     : Clement Jamin


#ifndef CGAL_TRIANGULATION_IO_H
#define CGAL_TRIANGULATION_IO_H

#include <CGAL/Epick_d.h>
#include <CGAL/Triangulation.h>
#include <sstream>
#include <iostream>

namespace CGAL {

template<typename K>
std::ostream &
operator<<(std::ostream & os, const typename Wrap::Point_d<K> & p)
{
  typename K::Cartesian_const_iterator_d it = p.cartesian_begin();
  os << *it;
  ++it;
  for ( ; it != p.cartesian_end() ; ++it)
  {
    os << " " << *it;
  }
  return os;
}

template<typename K>
std::ostream &
operator<<(std::ostream & os, const typename Wrap::Weighted_point_d<K> & p)
{
  return os << p.point();
}


template<typename K>
std::istream &
operator>>(std::istream &is, typename Wrap::Point_d<K> & p)
{
  typedef typename Wrap::Point_d<K> P;
  typedef typename K::FT FT;
  std::vector<FT> coords;
  
  std::string line;
  for(;;)
  {
    if (!std::getline(is, line))
      return is;
    if (line != "")
      break;
  }
  std::stringstream line_sstr(line);
  FT temp;
  while (line_sstr >> temp)
    coords.push_back(temp);

  p = P(coords.begin(), coords.end());
  return is;
}

template<typename K>
std::istream &
operator>>(std::istream &is, typename Wrap::Weighted_point_d<K> & wp)
{
  typedef typename Wrap::Point_d<K>           P;
  typedef typename Wrap::Weighted_point_d<K>  WP;
  typedef typename K::FT FT;

  std::string line;
  for(;;)
  {
    if (!std::getline(is, line))
      return is;
    if (line != "")
      break;
  }
  std::stringstream line_sstr(line);
  FT temp;
  std::vector<FT> coords;
  while (line_sstr >> temp)
    coords.push_back(temp);
  
  std::vector<FT>::iterator last = coords.end() - 1;
  P p = P(coords.begin(), last);
  wp = WP(p, *last);

  return is;
}

template < class GT, class TDS >
std::ostream &
export_triangulation_to_off(std::ostream & os, 
                            const Triangulation<GT,TDS> & tr,
                            bool in_3D_export_surface_only = true)
{
  typedef Triangulation<GT,TDS>                         Tr;
  typedef typename Tr::Vertex_const_handle              Vertex_handle;
  typedef typename Tr::Vertex_const_iterator            Vertex_iterator;
  typedef typename Tr::Finite_vertex_const_iterator     Finite_vertex_iterator;
  typedef typename Tr::Full_cell_const_handle           Full_cell_handle;
  typedef typename Tr::Finite_full_cell_const_iterator  Finite_full_cell_iterator;
  typedef typename Tr::Full_cell_const_iterator         Full_cell_iterator;
  typedef typename Tr::Full_cell                        Full_cell;
  typedef typename Full_cell::Vertex_handle_const_iterator Full_cell_vertex_iterator;
  
  if (tr.maximal_dimension() < 2 || tr.maximal_dimension() > 3)
  {
    std::cerr << "Warning: export_tds_to_off => dimension should be 2 or 3.";
    os << "Warning: export_tds_to_off => dimension should be 2 or 3.";
    return os;
  }

  size_t n = tr.number_of_vertices();

  std::stringstream output;
  
  // write the vertices
  std::map<Vertex_handle, int> index_of_vertex;
  int i = 0;
  for(Finite_vertex_iterator it = tr.finite_vertices_begin(); 
      it != tr.finite_vertices_end(); ++it, ++i)
  {
    output << *it;
    if (tr.maximal_dimension() == 2)
      output << " 0";
    output << std::endl;
    index_of_vertex[it.base()] = i;
  }
  CGAL_assertion( i == n );
  
  size_t number_of_triangles = 0;
  if (tr.maximal_dimension() == 2)
  {
    for (Finite_full_cell_iterator fch = tr.finite_full_cells_begin() ;
         fch != tr.finite_full_cells_end() ; ++fch)
    {
      output << "3 ";
      for (Full_cell_vertex_iterator vit = fch->vertices_begin() ;
           vit != fch->vertices_end() ; ++vit)
      {
        output << index_of_vertex[*vit] << " ";
      }
      output << std::endl;
      ++number_of_triangles;
    }
  }
  else if (tr.maximal_dimension() == 3)
  {
    if (in_3D_export_surface_only)
    {
      // Parse boundary facets
      for (Full_cell_iterator fch = tr.full_cells_begin() ;
           fch != tr.full_cells_end() ; ++fch)
      {
        if (tr.is_infinite(fch))
        {
          output << "3 ";
          for (Full_cell_vertex_iterator vit = fch->vertices_begin() ;
               vit != fch->vertices_end() ; ++vit)
          {
            if (!tr.is_infinite(*vit))
              output << index_of_vertex[*vit] << " ";
          }
          output << std::endl;
          ++number_of_triangles; 
        }
      }
    }
    else
    {
      // Parse boundary facets
      for (Finite_full_cell_iterator fch = tr.finite_full_cells_begin() ;
           fch != tr.finite_full_cells_end() ; ++fch)
      {
        output << "3 "
               << index_of_vertex[fch->vertex(0)] << " "
               << index_of_vertex[fch->vertex(1)] << " "
               << index_of_vertex[fch->vertex(2)]
               << std::endl;
        output << "3 "
               << index_of_vertex[fch->vertex(0)] << " "
               << index_of_vertex[fch->vertex(2)] << " "
               << index_of_vertex[fch->vertex(3)]
               << std::endl;
        output << "3 "
               << index_of_vertex[fch->vertex(1)] << " "
               << index_of_vertex[fch->vertex(2)] << " "
               << index_of_vertex[fch->vertex(3)]
               << std::endl;
        output << "3 "
               << index_of_vertex[fch->vertex(0)] << " "
               << index_of_vertex[fch->vertex(1)] << " "
               << index_of_vertex[fch->vertex(3)]
               << std::endl;
        number_of_triangles += 4;
      }
    }
  }

  os << "OFF \n"
     << n << " " 
     << number_of_triangles << " 0\n"
     << output.str();

  return os;
}

} //namespace CGAL

#endif // CGAL_TRIANGULATION_IO_H
