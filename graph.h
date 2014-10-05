/**
 @file graph.h
 Author         Ken Zyma (kzyma650)\n
 Creation:      Date: Oct. 1, 2014\n
 Due Date:      Oct. 8, 2014\n
 Courses:       CSC402\n
 Professor:     Dr. Speigel\n
 Assignment:    Project 2\n
 Filename:      graph.h\n
 
 Graph interface provides all operations build and query information
 about a graph. Extension allows various data structures to be used
 with type GraphAlgorithm.
 
 */

#ifndef ADS_PROJECT2_GRAPH
#define ADS_PROJECT2_GRAPH

#include <iostream>
#include <map>
#include <vector>

/**
 * Edge holds the cost and destination of an edge in a graph.
 */
struct Edge{
    int cost;
    int destinationVertex;
};

/**
 * Interface Graph provides a prototype for graph behavior.
 */
class Graph{
public:
    
    /**
     * @brief Destroy instance of Graph.
     * 
     * Destroy instance of type Graph. Derived classes
     * must handle memory management.
     */
    virtual ~Graph()=0;
    
    /**
     * @brief Add edge to graph.
     *
     * Add edge to graph from a stated vertex.
     *
     * @param sourceVertex Import parameter. The vertex which to
     * connect the parameter edge. If the vertex does not currently
     * exist in the graph, it will be added.
     * @param edge Import parameter. The edge to add to a vertex.
     * @return void
     */
    virtual void addEdge(const int sourceVertex,const Edge edge)=0;
    
    /**
     * @brief Add edge to graph.
     *
     * Add edge, cost and destination vertex, to graph from a 
     * stated vertex.
     *
     * @param sourceVertex Import parameter. The vertex which to
     * connect the parameter edge. If the vertex does not currently
     * exist in the graph, it will be added.
     * @param cost Import parameter. The cost of the edge.
     * @param destinationVertex Import parameter. The vertex adjacent to
     * the starting vertex.
     * @return void
     */
    virtual void addEdge(const int sourceVertex,
                      const int cost,
                      const int destinationVertex)=0;
   
    /**
     * @brief Return adjacent edges from vertex.
     * 
     * Return std::vector<Edge> of adjacent edges from parameter vertex.
     * If vertex does not exist or no edges exist from vertex, an
     * empty std::vector<Edge> is returned.
     *
     * @param vertex Import parameter. Vertex to find adjacent edges.
     * @return std::vector<Edge>
     */
    virtual const std::vector<Edge> getAdjacent(int vertex)const=0;
    
    /**
     * @brief Return adjacent edges from vertex.
     *
     * Return std::vector<Edge> of adjacent edges from parameter vertex.
     * If vertex does not exist or no edges exist from vertex, an
     * empty std::vector<Edge> is returned.
     *
     * @param vertex Import parameter. Vertex to find adjacent edges.
     * @return std::vector<Edge>
     */
    virtual const std::vector<Edge> at(int vertex) const=0;
    
    /**
     * @brief Return all vertices.
     *
     * Return std::vector<int> of all vertices in graph.
     *
     * @return std::vector<int>
     */
    virtual const std::vector<int> getVertices()const=0;
    
    /**
     * @brief Return true if vertex is in graph, false otherwise.
     *
     * Return true if vertex is in graph, false otherwise.
     *
     * @param vertex Import parameter. The vertex to check if it is in
     * this graph.
     * @return true if vertex is in graph, false otherwise.
     */
    virtual bool isInGraph(const int vertex)const = 0;
};

/**
 * @brief Insert representation of Graph to stream os.
 *
 * Insert textual representation of Graph to stream os. Starting
 * vertice, cost of edge, and destination vertex is listed, in a 
 * format similar to adjacency list.
 *
 * @param os Import/Export. Stream to insert graph reprentation.
 * @param graph Import. The graph to insert to stream os.
 * @return std::ostream& the stream.
 */
std::ostream& operator<<(std::ostream& os, const Graph& graph);

/**
 * AdjacencyList data structure implemenation of a Graph.
 */
class AdjacencyList_Graph:public Graph{
protected:
    std::multimap<int,Edge> adjList;
public:
    /**
     * @brief Constuct AdjacencyList_Graph.
     *
     * Constuct an instance of AdjacencyList_Graph.
     */
    AdjacencyList_Graph();
    
    /**
     * @brief Destroy instance of AdjacencyList_Graph.
     *
     * Destroy instance of type AdjacencyList_Graph.
     */
    ~AdjacencyList_Graph();
    
    /**
     * @brief Add edge to graph.
     *
     * Add edge to graph from a stated vertex.
     *
     * <p>Complexity is logrithmic for a single element inserted.</p>
     *
     * @param sourceVertex Import parameter. The vertex which to
     * connect the parameter edge. If the vertex does not currently
     * exist in the graph, it will be added.
     * @param edge Import parameter. The edge to add to a vertex.
     * @return void
     */
    void addEdge(const int sourceVertex,const Edge edge);
    
    /**
     * @brief Add edge to graph.
     *
     * Add edge, cost and destination vertex, to graph from a
     * stated vertex.
     *
     * <p>Complexity is logrithmic for a single element inserted.</p>
     *
     * @param sourceVertex Import parameter. The vertex which to
     * connect the parameter edge. If the vertex does not currently
     * exist in the graph, it will be added.
     * @param cost Import parameter. The cost of the edge.
     * @param desinationVertex Import parameter. The vertex adjacent to
     * the starting vertex.
     * @return void
     */
    void addEdge(const int sourceVertex,
                         const int cost,
                         const int destinationVertex);
    
    /**
     * @brief Return adjacent edges from vertex.
     *
     * Return std::vector<Edge> of adjacent edges from parameter vertex.
     * If vertex does not exist or no edges exist from vertex, an
     * empty std::vector<Edge> is returned.
     *
     * <p>Complexity is O(|e|*log(|v|)) amortized time. Where |e| is the
     * number of edges connected to the vertex and |v| is the number
     * of vertices.</p>
     *
     * @param vertex Import parameter. Vertex to find adjacent edges.
     * @return std::vector<Edge>
     */
    const std::vector<Edge> getAdjacent(int vertex) const;
    
    /**
     * @brief Return adjacent edges from vertex.
     *
     * Return std::vector<Edge> of adjacent edges from parameter vertex.
     * If vertex does not exist or no edges exist from vertex, an
     * empty std::vector<Edge> is returned.
     *
     * <p>Complexity is O(|e|*log(|v|)) amortized time. Where |e| is the
     * number of edges connected to the vertex and |v| is the number
     * of vertices.</p>
     *
     * @param vertex Import parameter. Vertex to find adjacent edges.
     * @return std::vector<Edge>
     */
    const std::vector<Edge> at(int vertex) const;
    
    /**
     * @brief Return all vertices.
     *
     * Return std::vector<int> of all vertices in graph.
     *
     * <p>Complexity is O(|v|). Number of vertices in the graph.</p>
     *
     * @return std::vector<int>
     */
    const std::vector<int> getVertices() const;
    
    /**
     * @brief Return true if vertex is in graph, false otherwise.
     *
     * Return true if vertex is in graph, false otherwise.
     *
     * <p>Complexity is logritmic in number of vertices. O(log|v|).
     *
     * @param vertex Import parameter. The vertex to check if it is in
     * this graph.
     * @return true if vertex is in graph, false otherwise.
     */
    bool isInGraph(const int startVertex)const;
};


#endif /* ADS_PROJECT2_GRAPH */
