### HTTP SERVER
This is an example of an HTTP Server. 
I will try to design and implement a full scale web server with optimizations in C.
Ideas were stolen from Udacity's Introduction to Operating System's course.


#### Design
Basic idea is to have a showcase of a fast web server.
So the basic design goals are:
 
 1. Multi threaded system
 2. Threads for doing work
 3. Helper threads
 4. MMAP for optimization of file reading
 5. Cache in application for all computational and I/O tasks
 6. Improvement in memory: DMA Alignment

 In order for all these to happen a modular design should be selected.

####  Modules

- Core server
    - Listener
    - Acceptor
- Client Handler
    - Request parser
    - Response sender
- Path calculator
- Header calculator
- File handler

#### Thread Design
Core server - 1 main thread
Listener & Acceptor - 1 thread
Client Handlers - Thread Pool pre-allocated
Path Calculator - 1 thread
Header calculator - 1 thread
File Handler - 1 thread
