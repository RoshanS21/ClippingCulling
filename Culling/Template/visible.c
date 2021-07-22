// Shrestha, Roshan
// rxs5263
// 2020-05-01

//----------------------------------------------------------
#include <stdio.h>

#include "visible.h"

//----------------------------------------------------------
int isVisible( Vertex *cameraPosition, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO:  Purpose:  Determine if the triangle represented by
  //          vertices v1, v2, and v3 is visible from the given
  //          camera position.
  //
  //        Compute the toTriangle vector from the camera position
  //          to v1 of the triangle.
  //
  //        Derive the surface normal for the triangle by
  //          computing the cross product of the vector from v1
  //          to v2 with the vector from v1 to v3.
  //
  //        Compute the angle between the toTriangle vector and
  //          the surface normal vector.
  //
  //        Return 1 if this angle indicates the triangle is
  //          visible from the camera position, 0 otherwise.

  Vertex a, b, surfaceNormal, toTriangle;

  toTriangle.x = v1->x - cameraPosition->x;
  toTriangle.y = v1->y - cameraPosition->y;
  toTriangle.z = v1->z - cameraPosition->z;

  a.x = v2->x - v1->x;
  a.y = v2->y - v1->y;
  a.z = v2->z - v1->z;
  
  b.x = v3->x - v1->x;
  b.y = v3->y - v1->y;
  b.z = v3->z - v1->z;
  
  surfaceNormal.x = a.y*b.z - a.z*b.y;
  surfaceNormal.y = a.z*b.x - a.x*b.z;
  surfaceNormal.z = a.x*b.y - a.y*b.x;

  double cosTheta = toTriangle.x*surfaceNormal.x + 
    toTriangle.y*surfaceNormal.y + toTriangle.z*surfaceNormal.z;

  if ( cosTheta < 0 ){
    return 1;
  }

  return 0;
}

//----------------------------------------------------------
