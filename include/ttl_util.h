//===========================================================================
//                                                                           
// File: ttl_util.h                                                          
//                                                                           
// Created: Jan 15 2000
//                                                                           
// Author: �yvind Hjelle <oyvind.hjelle@sintef.no>,
//         ............. <............ @sintef.no>
//                                                                           
// Revision: $Id: ttl_util.h,v 1.11 2005-01-19 10:56:06 afr Exp $
//                                                                           
// Description:
//                                                                           
//===========================================================================
// Copyright (c) 2000 SINTEF Applied Mathematics
//===========================================================================

#ifndef _TTL_UTIL_H_
#define _TTL_UTIL_H_

#ifdef _MSC_VER
#  if _MSC_VER < 1300
#    include <minmax.h>
#  endif
#endif

#ifndef TTL_USE_OLD_STD
  #include <vector>
  #include <algorithm>
#else
  #include <vector.h>
  #include <algorithm.h>
#endif

/** \brief Utilities
*   
*   This name space contains utility functions for TTL.<br>
*   Point and vector algebra such as scalar product and cross product
*   between vectors are implemented here.
*   These functions are required by functions in the \ref ttl namespace
*   where they are assumed to be present in the \ref hed::TTLtraits "TTLtraits" class.
*   Thus, the user can call these functions from the traits class.
*   For efficiency reasons, the user may consider implementing these
*   functions in the the API directly on the actual data structure;
*   see \ref api.<br>
*
*   \note
*   - Cross product between vectors in the xy-plane delivers a scalar,
*     which is the z-component of the actual cross product
*     (the x and y components are both zero).
*
* \see ttl and \ref api
* \author �yvind Hjelle, oyvind.hjelle@sintef.no<br>
*         .............  .......................... @sintef.no
*/
namespace ttl_util {
  
  /** @name Computational geometry */
  //@{
  /** Scalar product between two 2D vectors
  *   \par Returns:
  *   \code dx1*dx2 + dy1*dy2 \endcode
  */
  template <class real_type>  
    real_type scalarProduct2d(real_type dx1, real_type dy1, real_type dx2, real_type dy2) {
    return dx1*dx2 + dy1*dy2;
  }
  
  /** Cross product between two 2D vectors. (The z-component of the actual cross product.)
  *   \par Returns:
  *   \code dx1*dy2 - dy1*dx2 \endcode
  *
  */
  template <class real_type>
    real_type crossProduct2d(real_type dx1, real_type dy1, real_type dx2, real_type dy2) {
    return dx1*dy2 - dy1*dx2;
  }
  
  /** Return a positive value if the 2d nodes/points \e pa, \e pb, and
  *   \e pc occur in counterclockwise order; a negative value if they occur
  *   in clockwise order; and zero if they are collinear.
  *
  *   \note
  *   This is a finite arithmetic fast version. It can be made more robust using
  *   exact arithmetic schemes by Jonathan Richard Shewchuk. See
  *   http://www.cs.cmu.edu/~quake/robust.html
  */
  template <class real_type>
  real_type orient2dfast(const real_type pa[2], const real_type pb[2], const real_type pc[2]) {
      real_type acx = pa[0] - pc[0];
      real_type bcx = pb[0] - pc[0];
      real_type acy = pa[1] - pc[1];
      real_type bcy = pb[1] - pc[1];
      return acx * bcy - acy * bcx;
  }

  /* Scalar product between 2D vectors represented as darts.<br>
  *
  *   \par Requires:
  *   - real_type DartType::x()
  *   - real_type DartType::y()
  */  

  /*
  template <class TTLtraits, class DartType>
    typename TTLtraits::real_type scalarProduct2d(const DartType& d1, const DartType& d2) {
    
    DartType d10 = d1;
    d10.alpha0();
    
    DartType d20 = d2;
    d20.alpha0();
    
    return scalarProduct2d( d10.x() - d1.x(), d10.y() - d1.y(), d20.x() - d2.x(), d20.y() - d2.y() );
  }
  */
  
  /* Scalar product between 2D vectors.<br>
  *   The first vector is represented by the given dart, and the second vector has
  *   direction from the node of the given dart - and to the given point.
  *
  *   \par Requires:
  *   - real_type DartType::x()    real_type DartType::y()
  *   - real_type PointType2d::x(),  real_type PointType2d::y()
  */
  /*
  template <class TTLtraits>
  typename TTLtraits::real_type scalarProduct2d(const typename TTLtraits::DartType& d, const typename TTLtraits::PointType2d& p) {
  
    typename TTLtraits::DartType d0 = d;
    d0.alpha0();
    
      return scalarProduct2d( d0.x() - d.x(), d0.y() - d.y(), p.x() - d.x(), p.y() - d.y() );
      }
  */
  
  /* Cross product between 2D vectors represented as darts.<br>
  *
  *   \par Requires:
  *   - real_type DartType::x(), real_type DartType::y()
  */
  /*
  template <class TTLtraits>
  typename TTLtraits::real_type crossProduct2d(const typename TTLtraits::DartType& d1, const typename TTLtraits::DartType& d2) {
  
    TTLtraits::DartType d10 = d1;
    d10.alpha0();
    
      TTLtraits::DartType d20 = d2;
      d20.alpha0();
      
        return crossProduct2d( d10.x() - d1.x(), d10.y() - d1.y(), d20.x() - d2.x(), d20.y() - d2.y() );
        }
  */
  
  
  /* Cross product between 2D vectors.<br>
  *   The first vector is represented by the given dart, and the second vector has
  *   direction from the node associated with given dart - and to the given point.
  * 
  *   \par Requires:
  *   - real_type DartType::x(), real_type DartType::y()
  */
  /*
  template <class TTLtraits>
  typename TTLtraits::real_type crossProduct2d(const typename TTLtraits::DartType& d, const typename TTLtraits::PointType2d& p) {
  
    TTLtraits::DartType d0 = d;
    d0.alpha0();
    
      return crossProduct2d( d0.x() - d.x(), d0.y() - d.y(), p.x() - d.x(), p.y() - d.y() );
      }
  */
  // Geometric predicates; see more robust schemes by Jonathan Richard Shewchuk at
  // http://www.cs.cmu.edu/~quake/robust.html
  
  /* Return a positive value if the 2d nodes/points \e d, \e d.alpha0(), and
  *   \e p occur in counterclockwise order; a negative value if they occur
  *   in clockwise order; and zero if they are collinear. The
  *   result is also a rough approximation of twice the signed
  *   area of the triangle defined by the three points.
  *
  *   \par Requires:
  *   - DartType::x() and DartType::y(), PointType2d::x(), PointType2d::y()
  */
  /*
  template <class TTLtraits, class DartType, class PointType2d>
  typename TTLtraits::real_type orient2dfast(const DartType& n1, const DartType& n2, const PointType2d& p) {
  return ((n2.x()-n1.x())*(p.y()-n1.y()) - (p.x()-n1.x())*(n2.y()-n1.y()));
  }
  */

  //@}

  
  /** @name Utilities involving points */
  //@{
  /** Create random data on the unit square
  *
  *  \param seed Initial value for pseudorandom number generator
  *
  *   \require
  *   Constructor \c PointType::PointType(double x, double y).
  *   For example, one can use \c std::pair<double,double>.
  *
  *   \note To deduce template argument for PointType the function must be
  *   called with the syntax: \c createRandomData<MyPoint>(...) where \c MyPoint
  *   is the actual point type.
  */
  template <class PointType>
    std::vector<PointType*>* createRandomData(int noPoints, int seed=1) {
    
#ifdef _MSC_VER
    srand(seed);
#else
    srand48((long int)seed);
#endif
    
    double x, y;
    std::vector<PointType*>* points = new std::vector<PointType*>(noPoints);
    typename std::vector<PointType*>::iterator it;
    for (it = points->begin(); it != points->end(); ++it) {
#ifdef _MSC_VER
      int random = rand();
      x = ((double)random/(double)RAND_MAX);
      random = rand();
      y = ((double)random/(double)RAND_MAX);
      *it = new PointType(x,y);
#else
      double random = drand48();
      x = random;
      random = drand48();
      y = random;
      *it = new PointType(x,y);
#endif
    }
    return points;
  }
  //@}
  
}; // end namespace 

#endif // _TTL_UTIL_H_
