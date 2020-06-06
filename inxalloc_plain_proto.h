
void inxalloc_Struct_Init( struct inXmem_s* p );

void* inxalloc( struct inXmem_s* p, size_t size );

int inxfree( struct inXmem_s* p, void* mem );

int inxfreefree( void* mem );

void inxalloc_Struct_Report( struct inXmem_s* p );

struct inXmem_s* inxalloc_Block_Parent( void* b );


int inyfree( void* mem );

void* inyalloc( size_t size );

void inyalloc_Report();

