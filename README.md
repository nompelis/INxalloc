# INxalloc

This is a wrapper for the C/C++ heap alloator that we all use. It wraps
that functionality and uses some auxillary structures such that it can keep
track (and report) the memory allocation of a process with some granularity.

Motivation

Suppose you have a piece of software that performs a number of tasks, and
for each task it needs to allocate memory, which we would like to be able
to report at a moment's notice. Wrapping the allocation and deallocation
calls allows us to explicitly keep track of the memory we allocate. Doing
this for different components separately can be done by having additional
structures. The presumption is that the memory required to keep track of
the memory usage is much less than the memory we are allocating for usage.
Having a "drop-in" replacement for the existing heap allocators can help
during process benchmarking and in performing diagnostics.

What this software dones and how to use it

TO BE CONTINUED...

IN 2020/04/22 (Earth day)

