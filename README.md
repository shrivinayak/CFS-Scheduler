# CFS-Scheduler
#### This is a simplifed implementation of Completely Fair Scheduler using Red Black Trees and Min Heap Data Structures in C++ 

CFS was added to linux kernel 2.6 and is the default scheduler there after. 

- This project uses red black trees for O(1) time complexity for job lookups.
- It makes use of min Heap picking up the least executed jobs in O(1) for multicore and O(log n) for single core processors. 


This is still in testing phase.
