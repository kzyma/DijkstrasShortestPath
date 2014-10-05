/**
 @file graph.cpp
 Author         Ken Zyma (kzyma650)\n
 Creation:      Date: Oct. 1, 2014\n
 Due Date:      Oct. 8, 2014\n
 Courses:       CSC402\n
 Professor:     Dr. Speigel\n
 Assignment:    Project 2\n
 Filename:      graph.cpp\n
 
 
 */

#include "graph.h"

/* Graph */
Graph::~Graph(){}

/* Graph- nonmember functions */
std::ostream& operator<<(std::ostream& os, const Graph& graph){
    std::vector<int> vertices = graph.getVertices();
    for (auto it=vertices.begin();it!=vertices.end();it++){
        std::cout<<*it;
        std::vector<Edge> adjInfo = graph.getAdjacent(*it);
        
        for (auto iad=adjInfo.begin();iad!=adjInfo.end();iad++){
            std::cout<<std::endl<<"=>("<<iad->cost<<") ";
            std::cout<<iad->destinationVertex<<" ";
        }
        std::cout<<std::endl;
    }
    return os;
}

/* AdjacencyList_Graph */
AdjacencyList_Graph::AdjacencyList_Graph(){}

AdjacencyList_Graph::~AdjacencyList_Graph(){}

void AdjacencyList_Graph::addEdge(const int sourceVertex,const Edge edge){
    adjList.insert(std::pair<int,Edge>(sourceVertex,edge));
}

void AdjacencyList_Graph::addEdge
(const int sourceVertex,
const int cost,
const int destinationVertex){
    Edge edge;
    edge.destinationVertex = destinationVertex;
    edge.cost = cost;
    AdjacencyList_Graph::addEdge(sourceVertex,edge);
}

const std::vector<Edge> AdjacencyList_Graph::getAdjacent
(int vertex)const{
    
    std::vector<Edge> adjEdges;
    //equal_range returns upper and lower bounds of key in multimap
    std::pair <std::multimap<int,Edge>::const_iterator,
        std::multimap<int,Edge>::const_iterator> ret;
    ret = adjList.equal_range(vertex);
    for (std::multimap<int,Edge>::const_iterator it=ret.first;
         it!=ret.second; ++it){
        adjEdges.push_back(it->second);
    }
    return adjEdges;
}

const std::vector<Edge> AdjacencyList_Graph::at(int vertex) const{
    return AdjacencyList_Graph::getAdjacent(vertex);
}

const std::vector<int> AdjacencyList_Graph::getVertices()
const{
    std::vector<int> vertices;
    for(std::multimap<int,Edge>::const_iterator it = adjList.begin(),
        end = adjList.end();
        it != end; it = adjList.upper_bound(it->first))
    {
        vertices.push_back(it->first);
    }
    return vertices;
}

bool AdjacencyList_Graph::isInGraph(const int vertex)const{
    auto it = adjList.find(vertex);
    if(it == adjList.end()){
        return false;
    }
    return true;
}

