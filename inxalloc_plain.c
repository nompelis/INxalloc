/******************************************************************************
 Copyright (c) 2020, Ioannis Nompelis
 All rights reserved.

 Redistribution and use in source and binary forms, with or without any
 modification, are permitted provided that the following conditions are met:
 1. Redistribution of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
 2. Redistribution in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
 3. All advertising materials mentioning features or use of this software
    must display the following acknowledgement:
    "This product includes software developed by Ioannis Nompelis."
 4. Neither the name of Ioannis Nompelis and his partners/affiliates nor the
    names of other contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.
 5. Redistribution or use of source code and binary forms for profit must
    have written permission of the copyright holder.
 
 THIS SOFTWARE IS PROVIDED BY IOANNIS NOMPELIS ''AS IS'' AND ANY
 EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL IOANNIS NOMPELIS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inxalloc.h"


//
// Function to initialize the structure storing memory data
//
__inline void inxalloc_Struct_Init( struct inXmem_s* p )
{
   p->id = -1;
   p->size = 0;
   p->num_alloc = 0;
   p->num_free = 0;
}


void* inxalloc( struct inXmem_s* p, size_t size )
{
#ifdef _DEBUG_
   char FUNC[] = "inxalloc";
#endif
   void* tmp;
   size_t size_hdr = sizeof( struct inXmemhdr_s );
   struct inXmemhdr_s* hdr;

   if( p == NULL ) {
#ifdef _DEBUG_
      fprintf( stdout, " [%s]  Incoming structure is null \n",FUNC);
#endif
      return NULL;
#ifdef _DEBUG_
   } else {
      fprintf( stdout, " [%s]  Incoming structure ID is %d \n",FUNC,p->id);
#endif
   }

   tmp = (void*) malloc( size + size_hdr );
   if( tmp != NULL ) {
#ifdef _DEBUG_
      fprintf( stdout, " [%s]  Allocated chunk (%ld bytes) at %p\n",
               FUNC, (long int) size, tmp );
#endif

      // increment the memory structure's size and number of allocations
      p->size += size;
      p->num_alloc += 1;

      // store header of block
      hdr = (struct inXmemhdr_s*) tmp;
      hdr->segment = p;              // parent memory structure
      hdr->size = size;              // size of block
      hdr->ialloc = p->num_alloc;    // allocation step

      // do a shift to offset from the start of the block's header
      tmp += size_hdr;
#ifdef _DEBUG_
      fprintf( stdout, " [%s]  Returning pointer at %p \n",FUNC,tmp);
#endif

      return tmp;
   } else {
#ifdef _DEBUG_
      fprintf( stdout, " [%s]  Could not allocate chunk (%ld bytes)\n",
               FUNC, (long int) size );
#endif
   }

   return NULL;
}


//
// Function to free a memory block from a segment
//
int inxfree( struct inXmem_s* p, void* mem )
{
#ifdef _DEBUG_
   char FUNC[] = "inxfree";
#endif
   size_t size_hdr = sizeof( struct inXmemhdr_s );
   struct inXmemhdr_s* hdr;
   void* tmp;
   size_t size;

   if( p == NULL ) {
#ifdef _DEBUG_
      fprintf( stdout, " [%s]  Incoming structure is null \n",FUNC);
#endif
      return 1;
#ifdef _DEBUG_
   } else {
      fprintf( stdout, " [%s]  Incoming structure ID is %d \n",FUNC,p->id);
#endif
   }

   if( mem == NULL ) {
#ifdef _DEBUG_
      fprintf( stdout, " [%s]  Incoming memory block ipoiner s null \n",FUNC);
#endif
      return 2;
#ifdef _DEBUG_
   } else {
      fprintf( stdout, " [%s]  Incoming memory block pointer %p \n",FUNC,mem);
#endif
   }

   tmp = mem - size_hdr;
   hdr = (struct inXmemhdr_s*) tmp;

   if( hdr->segment != p ) {
      fprintf( stdout, "Error: block not associated with this tructure!\n");
      fprintf( stdout, "       Not performing any freeing.\n");
      return 3;
   }

   size = hdr->size;

   free( tmp );

   p->size -= size;
   p->num_free += 1;

   return 0;
}



//
// Function to report memory usage
//
void inxalloc_Struct_Report( struct inXmem_s* p )
{
#ifdef _DEBUG_
   char FUNC[] = "inxalloc_Struct_Report";
#endif
   if( p == NULL ) {
      fprintf( stdout, "Incoming inXalloc structure pointer is null \n");
      return;
#ifdef _DEBUG_
   } else {
      fprintf( stdout, " [%s]  Incoming inXalloc structure pointer %p \n",
               FUNC, p );
#endif
   }

   fprintf( stdout, "Memory struct ID: %d \n",p->id);
   fprintf( stdout, "Memory struct size: %ld \n",(long int) p->size);
   fprintf( stdout, "Memory struct number of allocations: %ld \n",p->num_alloc);
   fprintf( stdout, "Memory struct number of frees: %ld \n",p->num_free);
}



//
// Function to query the memory segment to which a block belongs
//
struct inXmem_s* inxalloc_Block_Parent( struct inXmemhdr_s* b )
{
#ifdef _DEBUG_
   char FUNC[] = "inxalloc_Block_Info";
#endif
   struct inXmemhdr_s* hdr;
   if( b == NULL ) {
      fprintf( stdout, "Incoming inXalloc block pointer is null \n");
      return NULL;
   } else {
      void* tmp = (void*) b;
      hdr = (struct inXmemhdr_s*) (tmp - sizeof(struct inXmemhdr_s));
#ifdef _DEBUG_
      fprintf( stdout, " [%s]  Incoming inXalloc block pointer %p \n",
               FUNC, b );
      fprintf( stdout, " [%s]  Created from segment at: %p (ID=%d)\n",
               FUNC, hdr->segment, hdr->segment->id );
      fprintf( stdout, " [%s]  Was allocation number: %ld \n",
               FUNC, hdr->ialloc );
#endif
   }
   return hdr->segment;
}


