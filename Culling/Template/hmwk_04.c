// Shrestha, Roshan
// rxs5263
// 2020-05-01
//----------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "projection.h"
#include "triangle.h"
#include "vertex.h"
#include "view.h"
#include "visible.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <modelFileName> <viewFileName>\n", argv[0] );
    exit( 1 );
  }

  //--------------------------------------
  // Load the desired model and view.
  Model *m = loadModel( argv[1] );
  View *v = loadView( argv[2] );

  // Compute the projection corresponding to the view.
  Projection *p = computeProjection( v );

  //--------------------------------------
  // Dump all of these data structures as a check.
  dumpModel( m );
  dumpView( v );
  dumpProjection( p );

  //--------------------------------------
  // Allocate a place for the projected versions of the vertices
  // to go.

  // TODO: Allocate enough space for the number of vertices the
  //       model has.  This will be the space for the projected
  //       versions of the vertices.  (Remember to check if the
  //       space got allocated OK!)
  Vertex *destination = (Vertex *) calloc( m->m_numVertices, sizeof(Vertex));
  if ( destination == NULL ) {
    fprintf( stderr, "Unable to allocate Vertex destination.\n" );
    exit( 1 );
  }

  // And now project the vertices into that space ...

  // TODO: Project the vertices of the model into the space you
  //       just allocated using projectVertexList2().
  projectVertexList2(p, m->m_vertex, m->m_numVertices, destination);

  //--------------------------------------
  // Print the canvas size for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  //--------------------------------------
  // Draw lines corresponding to the viewport region.

  // TODO: Print four 'l' lines, corresponding to the
  //         the edges of the viewport region.
  //       Start in the lower-left corner (xMin, yMin) and draw
  //         the lines going counter-clockwise.
  printf("l %6d %8d %8d %8d\n",
    v->m_portalXMin, v->m_portalYMin, v->m_portalXMax, v->m_portalYMin);
  printf("l %6d %8d %8d %8d\n",
    v->m_portalXMax, v->m_portalYMin, v->m_portalXMax, v->m_portalYMax);
  printf("l %6d %8d %8d %8d\n",
    v->m_portalXMax, v->m_portalYMax, v->m_portalXMin, v->m_portalYMax);
  printf("l %6d %8d %8d %8d\n",
    v->m_portalXMin, v->m_portalYMax, v->m_portalXMin, v->m_portalYMin);

  //--------------------------------------
  // Construct a Vertex representing the camera position.
  // Remember, if the camera distance is 0.0 (representing a
  // PARALLEL projection), it should be thought of as being
  // very far away.

  // TODO: Construct a Vertex holding the worldspace position of
  //       the camera.  If the projection is PARALLEL, remember
  //       that the camera's z coordinate should be at effectively
  //       "infinity".
  Vertex *cameraPosition = (Vertex *) calloc(1, sizeof(Vertex));
  if (cameraPosition == NULL ){
    fprintf( stderr, "Unable to allocate Vertex cameraPosition.\n" );
    exit( 1 );
  }
  cameraPosition->x = 0;
  cameraPosition->y = 0;

  if ( v->m_cameraDistance == 0 ){
    cameraPosition->z = HUGE_VAL;
  }else{
    cameraPosition->z = v->m_cameraDistance;
  }

  //--------------------------------------
  // Consider each of the faces of the model.  If the face is
  // not visible (that is, does not face the camera position),
  // ignore it.  If the face is visible, dump its triangle.
  //
  // Check for visibility using the isVisible() function and the
  // ORIGINAL vertex positions, the ones in m->m_vertex.  These
  // are still in worldspace.
  //
  // Dump the triangle using the enhanced dumpTriangle() function
  // and the PROJECTED vertex positions.  These are in screen
  // space.

  // TODO: For each face of the model, draw the triangle
  //       represented by its three vertices using the enhanced
  //       version of dumpTriangle().  Draw the triangle ONLY IF
  //       the triangle is visible (use isVisible() to determine
  //       this).
  int i;
  
  for( i=0; i < m->m_numFaces; i++ )
  {
    int v1 = (m->m_face[i]).v1, v2 = (m->m_face[i]).v2, v3 = (m->m_face[i]).v3;

    if ( isVisible( cameraPosition, &m->m_vertex[v1], &m->m_vertex[v2], &m->m_vertex[v3] ) ){
      dumpTriangle( v, &destination[v1], &destination[v2], &destination[v3] );
    }
  }

  //--------------------------------------
  // Free all of our allocated resources ...

  // TODO: Free all allocated structures.
  if (m != NULL) free(m);
  if (v != NULL) free(v);
  if (p != NULL) free(p);
  if (destination != NULL) free(destination);
  if (cameraPosition != NULL) free(cameraPosition);

  // ... and exit with no error.

  // TODO: Return from main indicating no error.
  return 0;
}

//----------------------------------------------------------

