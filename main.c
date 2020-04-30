//
// a code to demonstrate the use of INxalloc
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inxalloc.h>


int main( int argc, char *argv[] )
{
   size_t isize;
   void *p1,*p2,*p3;
   struct inXmem_s s;


   inxalloc_Struct_Init( &s );
   s.id = 666;    // user-set ID of memory segment

   isize = 32;
   p1 = (void*) inxalloc( &s, isize );
   isize = 64;
   p2 = (void*) inxalloc( &s, isize );
   isize = 128;
   p3 = (void*) inxalloc( &s, isize );

   inxalloc_Struct_Report( &s );


   inxalloc_Block_Parent( p1 );
   inxalloc_Block_Parent( p2 );


   inxfree( &s, p1 );
   inxalloc_Struct_Report( &s );

   inxfree( &s, p2 );
   inxalloc_Struct_Report( &s );

   inxfreefree( p3 );
   inxalloc_Struct_Report( &s );

   return EXIT_SUCCESS;
}


