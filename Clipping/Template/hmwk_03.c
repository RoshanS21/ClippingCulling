// Shrestha, Roshan
// rxs5263
// 2020-04-24
//----------------------------------------------------------
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "line.h"
#include "view.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <lineFileName> <viewFileName\n", argv[0] );
    exit( 1 );
  }

  char *lineFileName = argv[1];
  char *viewFileName = argv[2];

  //--------------------------------------
  // Load the view information.  We're interested in the canvas
  // size and the portal dimensions (both measured in pixels).
  View *v;

  v = loadView( viewFileName );
  dumpView( v );

  //--------------------------------------
  // Print the canvas size for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  //--------------------------------------
  // Open the file with proposed lines to draw.
  FILE *fp = fopen( lineFileName, "r" );
  if ( fp == NULL ) {
    fprintf( stderr, "%s: Unable to open '%s' for read.\n",
      argv[0], lineFileName );
    exit( 1 );
  }

  //--------------------------------------
  // Process each proposed line ...
  // TODO: Read each line from the proposed line file (it was
  //         opened for you above).
  //       For every line whose first non-whitespace character is
  //         an 'l':
  //         Scan the four numbers (floating point!) following the
  //           'l' to get the p1X, p1Y and p2X, p2Y of the two
  //           endpoints of the line.
  //         Construct a Line holding these values.
  //         Call clipLine() with a pointer to that Line and the
  //           for sides of the portal (from the View structure).
  //         If clipLine() returns 1, use dumpLine() to dump the
  //           line to the output.
  //         If clipLine() returns 0, print a Rejected message.
  //         In either case, count how many lines get dumped and
  //           how many lines get rejected.
  //
  //       After all lines from the file have been processed,
  //         print the line statistics (i.e., how many dumped,
  //         how many rejected.)
  //
  //       You can see the format of the messages by taking a look
  //         at any of the Results/ files.

  char   *line  = NULL;
  size_t  len   = 0;
  int     lineNum = 0;
  
  int numDumpLine = 0, numRejectLine = 0;
  Line *L = (Line *) calloc( 1, sizeof( Line ));

  while ( getline( &line, &len, fp ) != -1 ) {
    lineNum++;

    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;

    if ( *ptr == 'l' ) {
      int conv = sscanf( ptr+1, " %lf %lf %lf %lf",
        &L->p1X, &L->p1Y, &L->p2X, &L->p2Y );

      if ( conv != 4 ) {
        fprintf( stderr, "hmwk_03.c: Unable to load line at line %d.", lineNum );
      }

      if ( clipLine( L, v->m_portalXMin, v->m_portalYMin, v->m_portalXMax, v->m_portalYMax ) == 1){
        dumpLine( L );
        numDumpLine++;
      }else{
      	printf( "# Rejected l %8.1f %8.1f %8.1f %8.1f\n", L->p1X, L->p1Y, L->p2X, L->p2Y);
        numRejectLine++;
      }
    }
  }

  printf( "#- Line statistics ---------------------\n" );
  printf( "# %6d lines drawn.\n", numDumpLine );
  printf( "# %6d lines rejected.\n", numRejectLine );
  printf( "#---------------------------------------\n");

  //--------------------------------------
  // Tidy up:  free any allocated memory, close the line file.
  freeView( v );

  if ( L != NULL ) {
    free( L );
  }

  fclose( fp );

  //--------------------------------------
  // Ta-da!  All done and no errors.
  return 0;
}

//----------------------------------------------------------
