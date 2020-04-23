
void inxalloc_Struct_Init( struct inXmem_s* p );

void* inxalloc( struct inXmem_s* p, size_t size );

int inxfree( struct inXmem_s* p, void* mem );

void inxalloc_Struct_Report( struct inXmem_s* p );

struct inXmem_s* inxalloc_Block_Parent( struct inXmemhdr_s* b );

