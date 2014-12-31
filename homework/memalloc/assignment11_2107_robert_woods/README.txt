README
1.	my_malloc.c has driver included as the "main" function in the file.
2.	Both my_malloc and my_free functions have a commented out section that prints the "heap" used by 
	my_malloc.
3.	Line 22 tests creating the heap the first time the function is run.
4.	Lines 23-24 writes to this memory allocated
5.	Line 27 tests my_free with no coalescing
6.	Line 28 tests my_free with left and right side coalescing
7.	Line 33 tests my_malloc when not enough memory exists on the heap.
8.	Line 34 tests my_free with right side coalescing
9. 	Line 35 tests my_free with left side coalescing
10.	Line 37 tests my_malloc with no memory called.