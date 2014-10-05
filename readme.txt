1.Overview:

Title:         Project 2
Author:        Ken Zyma (kzyma650)
Creation:      Date: October 1, 2014
Due Date:      October 8, 2014
Courses:       CSC402
Professor:     Dr. Speigel
Assignment:    Project 2

Application reads an adjcancy list from file and outputs the least
cost path to every other vertex from a starting vertex, using
Dijkstra's shortest path algorithm. The starting vertex can either
be explicitly stated via command line argument or default's to the
first vertex read if none is stated.

2.Documentation:

    Documentation for this project is located at:

    http://acad.kutztown.edu/~kzyma650/Project2/index.html

3.Compilation and Execution:

    1)Run make utility
        e.g. >>make
    2)Execute shortest with textfile and optional
        starting vertex argument
        e.g. >>./shortest <filename><start vertex(opt)>

    By default (no start vertex), the starting vertex will
    be the first vertex read by file. This is the vertex from
    which shortest paths are found to all reachable vertices.

4.Design:

    See the paper (due at a later time) for full anaysis of data
    structures choosen. The overall design of this project may differ greatly
    from other projects implementing the same algorithm, as more overhead was
    used to construct an initial code base and objects to promote reuse.
    Under the assumption that I may want to implement other shortest
    path algorithms and try various graph representations, base class
    Graph and GraphAlgorithm were used as interfaces to there implementations
    in AdjacencyList_Graph and Dijstra.

    Another part that is potentially different deals with the output format.
    If a vertex is unreachable, it is not output (with the original cost set
    to infinity). Instead, in the interest of what I felt was improved
    readability, these are not shown.

    Finally, one interesting piece of code (this is also docuemnted in the low
    level comments in the source code as well):

    <line 151 in Paths.cpp>
    std::make_heap(const_cast<Path**>(&pQueue.top()),
        const_cast<Path**>(&pQueue.top()) + pQueue.size(),
        Path_GreaterCompare());

    Using a priority_queue filled with pointers to a vertex,path and cost was
    the idea for sorting low to high cost path's effeciently (logrithmic).
    Preliminary testing of this showed that make_heap() is not called from
    priority_queue when top() is called. This is nessesary, since the 'cost'
    of a path may have changed while in the queue. One way to deal with this
    would be to derive my own specialized priority_queue, and simply call
    make_heap() anytime top() is called. However, since this piece of code is
    isolated I decided to exploit the fact that a std::vector was used as the
    underlying container, and that a std::vector is promised to be stored in
    contigous memory. Thus, I was able to indirectly get to the underlying
    container and call make_heap myself. Note this is cannot be promised to
    if the container type is changed, as other containers do not garentee
    contigous storage.

5.Bugs:

	None Known
