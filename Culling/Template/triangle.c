// Shrestha, Roshan
// rxs5263
// 2020-05-01
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "triangle.h"

//----------------------------------------------------------
void dumpTriangle( View *view, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO: Using a Line structure and calling clipLine(), check
  //         each of the three lines v1->v2, v2->v3, v3->v1 for
  //         clipping status and print an 'l' line for those that
  //         are not rejected.  Do the lines in that order!

  Line *L = (Line *) calloc(1, sizeof(Line));
  L->p1X = v1->x;
  L->p1Y = v1->y;
  L->p2X = v2->x;
  L->p2Y = v2->y;

  int result;

  result = clipLine(L, view->m_portalXMin, view->m_portalYMin, view->m_portalXMax, view->m_portalYMax);
  if(result == 1){
  	dumpLine(L);
  }

  L->p1X = v2->x;
  L->p1Y = v2->y;
  L->p2X = v3->x;
  L->p2Y = v3->y;

  result = clipLine(L, view->m_portalXMin, view->m_portalYMin, view->m_portalXMax, view->m_portalYMax);
  if(result == 1){
  	dumpLine(L);
  }

  L->p1X = v3->x;
  L->p1Y = v3->y;
  L->p2X = v1->x;
  L->p2Y = v1->y;

  result = clipLine(L, view->m_portalXMin, view->m_portalYMin, view->m_portalXMax, view->m_portalYMax);
  if(result == 1){
  	dumpLine(L);
  }

  if (L != NULL){
  	free(L);
  }
}

//----------------------------------------------------------

