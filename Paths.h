/**
 @file paths.h
 Author         Ken Zyma (kzyma650)\n
 Creation:      Date: Oct. 1, 2014\n
 Due Date:      Oct. 8, 2014\n
 Courses:       CSC402\n
 Professor:     Dr. Speigel\n
 Assignment:    Project 2\n
 Filename:      paths.h\n
 
 GraphAlgorithm interface provides all operations for functor GraphAlgorithm
 subclasses.
 
 */

#ifndef ADS_PROJECT2_PATHS
#define ADS_PROJECT2_PATHS

#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <queue>
#include <functional>
#include <stdexcept>

#include "graph.h"

/**
 * Path is the path (list of vertices) container to a destination vertex.
 * Path also contains operations to query information about the path and
 * desination vertex, such as isMarked().
 */
class Path{
private:
    int cost;
    std::vector<int>path;
    int endVertex;
    bool marked;
public:
    /**
     * @brief Construct Path.
     *
     * Construct a type Path instance, with a specified ending vertex.
     * @param endVertex Import parameter. The destination vertex of the
     * path.
     */
    Path(const int endVertex);
    
    /**
     * @brief Assign contents of rhs path to this path.
     *
     * Assignemnt operator overloaded to make a deep copy of parameter
     * rhs for this Path instance.
     * @param rhs Import parameter. The Path instance to copy.
     * @return Instance of this path.
     */
    Path& operator=(const Path& rhs);
    
    /**
     * @brief Set cost of path.
     *
     * <p>Complexity is constant.</p>
     *
     * Set cost of path.
     * @param cost Import parameter. Cost to set the path to.
     */
    void setCost(const int cost);
    
    /**
     * @brief Get cost of path.
     *
     * <p>Complexity is constant.</p>
     *
     * Get cost of path.
     * @return cost of path.
     */
    int getCost()const;
    
    /**
     * @brief Set path.
     *
     * <p>Complexity is constant.</p>
     *
     * Set path, which is a std::vector<int> of vertices (type integer).
     * @param path Import paramter.
     */
    void setPath(const std::vector<int> path);
    
    /**
     * @brief Return path.
     *
     * <p>Complexity is constant.</p>
     *
     * Return path, std::vector<int>, containing vertices (type integer).
     * @return std::vector<int> the path.
     */
    std::vector<int> getPath()const;
    
    /**
     * @brief Append vertex to path.
     *
     * <p>Constant (amortized time). If resize does happen addToPath
     * could be up to linear in size, O(pathLength).</p>
     *
     * Append vetex to path.
     * @param vertex Import parameter. The vertex to append to path.
     */
    void addToPath(const int vertex);
    
    /**
     * @brief Return destination vertex.
     *
     * <p>Complexity is constant.</p>
     *
     * Return destination vertex.
     * @return the destination vertex, int.
     */
    int getEndVertex()const;
    
    /**
     * @brief Return true if vertex is marked, false otherwise.
     *
     * <p>Complexity is constant.</p>
     *
     * Check if destination vertex is marked.
     * @return true if vertex is marked, false otherwise
     */
    bool isMarked()const;
    
    /**
     * @brief Mark destination vertex.
     *
     * <p>Complexity is constant.</p>
     *
     * Mark destination vertex.
     */
    void markVertex();
    
    /**
     * @brief Get size of path.
     *
     * <p>Complexity is constant.</p>
     *
     * Return size of path, the number of vertices in path.
     * @return size of path.
     */
    int size();
    
    /**
     * @brief Get the vertex at index of path.
     *
     * <p>Complexity is constant.</p>
     *
     * Get the vertex at parameter index of path.
     * @throws out_of_range if index is out of the range of path.
     * @param index Import parameter. Index to get a vertice in path.
     */
    int at(int index);
};


/**
 * @brief Test if p1 < p2.
 * 
 * Return true if p1 is less than p2, false otherwise.
 * @param p1 Import parameter.
 * @param p2 Import parameter.
 * @return true if p1<p2, false otherwise.
 */
bool operator < (const Path &p1,const Path &p2);

/**
 * @brief Test if p1 > p2.
 *
 * Return true if p1 is greater than p2, false otherwise.
 * @param p1 Import parameter.
 * @param p2 Import parameter.
 * @return true if p1>p2, false otherwise.
 */
bool operator > (const Path &p1,const Path &p2);

/**
 * @brief Insert representation of path to stream os.
 *
 * Insert textual representation of path to stream os. Cost of edge, 
 * and destination vertex is listed, in a format similar to 
 * adjacency list.
 *
 * @param os Import/Export. Stream to insert graph reprentation.
 * @param path Import paramter. The path to insert to stream os.
 * @return std::ostream& the stream.
 */
std::ostream& operator<<(std::ostream& os, const Path& path);

/**
 * Functor to compare two pointers of Path instances. Comparison used
 * is (a [greater than] b).
 */
class Path_GreaterCompare{
public:
    /** @brief Return true is a > b, false otherwise.
     *
     * Return true is a > b, false otherwise.
     * @param a Import parameter.
     * @param b Import parameter.
     */
    bool operator()(const Path* a, const Path* b);
};

/**
 * Interface for shortest path graph aglorithm functors.
 */
class GraphAlgorithm{
public:
    
    /**
     * @brief Destroy instance of GraphAlgorithm.
     *
     * Destroy instance of type GraphAlgorithm. Derived classes
     * must handle memory management.
     */
    virtual ~GraphAlgorithm()=0;
    
    /**
     * @brief Execute shortest path algorithm.
     *
     *
     * Execute shortest path algorithm.
     * @param graph Import parameter. The graph to parse.
     * @param startVertex Import parameter. The vertex to start the 
     * shortest path search from.
     */
    virtual const std::map<int,Path>* operator()
    (const Graph& graph,const int startVertex)const=0;
};

/**
 * @brief Insert representation of all paths to stream os.
 *
 * Insert textual representation of starting vertice and all paths 
 * to stream os. Starting Vertex, cost of path, and destination vertex is
 * listed.
 *
 * @param os Import/Export. Stream to insert graph reprentation.
 * @param paths Import paramter. A map of paths to insert to stream os, where
 * the key of the map is the starting vertice.
 * @return std::ostream& the stream.
 */
std::ostream& operator<<(std::ostream& os, const std::map<int,Path> paths);

/**
 * Functor Dijkstra's shortest path algorithm, where all all shortest paths
 * from a starting vertex are returned.
 */
class Dijkstra:public GraphAlgorithm{
public:
    
    /**
     * @brief Destroy instance of Dijkstra.
     *
     * Destroy instance of type Dijkstra. Must override in any
     * derived class to properly manage memory.
     */
    ~Dijkstra();
    
    /**
     * @brief Execute Dijkstra's shortest path algorithm.
     * 
     * <p>Complexity is O(|e|log|v|), assuming |v| is O(|e|),
     * or a connected graph worse case.</p>
     *
     * Execute Dijkstra's shortest path algorithm.
     * @param graph Import parameter. The graph to parse.
     * @param startVertex Import parameter. The vertex to start the shortest
     * path search from.
     */
    const std::map<int,Path>* operator()
    (const Graph& graph,const int startVertex)const;
};

#endif /* ADS_PROJECT2_PATHS*/
