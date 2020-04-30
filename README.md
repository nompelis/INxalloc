# INxalloc

This is a wrapper for the C/C++ heap allocator that we all use. It wraps
existing functionality and uses some auxillary structures such that it can keep
track (and report) the memory allocation of a process with some granularity.
Granularity implies that the programmer can associate a given allocation
with an internal structure, grouping individual memory allocations in clusters.

- Motivation

Suppose you have a piece of software that performs a number of tasks, and
for each task it needs to allocate memory, which we would like to be able
to report at a moment's notice. Wrapping the allocation and deallocation
calls allows us to explicitly keep track of the memory we allocate. Doing
this for different components separately can be done by having additional
structures. The presumption is that the memory required to keep track of
the memory usage is much less than the memory we are allocating for tasks.
Having a "drop-in" replacement for the existing heap allocators can help
during process benchmarking and during performing diagnostics.

- What this software does and how to use it

Look in the example "main,c" on how to use it. You need to statically create
(or allocate on your own) a struct of type "inXmem_s" for every component of
your software for which you want to keep track of memory usage. You need to
pass to this API the pointer to this structure every time you allocate a
block of memory. You can very quickly abstract its use with some preprocessor
directives (more on this later).

The API uses the structs to keep track of the number of allocations and
the total memory usage. But each block can query back the structure under
which it was attached with a query. The way this works is typical of how
operating systems keep track of heap allocations, by having each chunk
(block) of allocated memory be augmented with a header that keeps track of
some pieces of information. In this case it keeps track of the pointer to
the inXmem_s structure that was used to allocate the memory, and also the
size of the allocated block. Keeping track of its size is what allows for
accurately keeping track of memory during deallocations.


TO BE CONTINUED...

IN 2020/04/23
IN 2020/04/30

