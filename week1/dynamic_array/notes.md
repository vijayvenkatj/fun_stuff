## Notes for making Dynamic array


### Allocations 

## BRK vs MMAP

- BRK is used for smaller allocation in malloc.
- BRK changes the program break value which seperates Heap in the Virtual Addr space.

- MMAP on the other hand is used for larger allocations in malloc.
- MMAP allocates new memory mappings seperate from the Heap in the Virtual Addr space.


## Malloc, Realloc, Free 

- Realloc is dangerous as It can invalidate previous pointer and get us a new pointer. 
- This might cause issues with other variables that are using this ref.

## ASan

- I have used fsanitize, I got Address Sanitizer on errors. 
- It stores shadow memory metadata to show us which byte is accessable and which is not. 
- It follows 1:8 ratio for it. Eg 04 means 4 bytes are valid and can be accessed. 


