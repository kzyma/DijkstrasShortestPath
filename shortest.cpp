/**
 @file shortest.cpp
 @mainpage      Project 2\n
 Author         Ken Zyma (kzyma650)\n
 Creation:      Date: Oct. 1, 2014\n
 Due Date:      Oct. 8, 2014\n
 Courses:       CSC402\n
 Professor:     Dr. Speigel\n
 Assignment:    Project 2\n
 Filename:      shortest.cpp\n
 
 Application reads an adjcancy list from file and outputs the least
 cost path to every other vertex from a starting vertex, using 
 Dijkstra's shortest path algorithm. The starting vertex can either 
 be explicitly stated via command line argument or default's to the 
 first vertex read if none is stated.
 
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <climits>
#include <sstream>
#include <ctime>
#include <stdexcept>
#include <chrono>

#include "graph.h"
#include "paths.h"

/**
 * @brief Read adjacency list from file.
 *
 * Read adjacency list from file and return an instance of Graph 
 * representing the adjacency list. Parameter startingVertex can be
 * used to get the first vertex read from the graph.
 *
 * @throws std::runtime_error if there is an error reading from file.
 * @param filename Import parameter. The name of the file to be read.
 * @param startingVertex Output parameter. Return the first vertex read
 * from file.
 * @return pointer to an instance of Graph.
 */
Graph* readAdjListFile(const std::string filename,int& startingVertex);

int main(int argc, const char* argv[]){

    if((argc < 2) || (argc > 3)){
        std::cout<<"usage: "<<argv[0]<<" <filename> <startVertex(opt)>";
        std::cout<<std::endl;
        return 0;
    }
    
    std::string filename = argv[1];
    Graph* graph;
    auto firstVertex(1);
    
    auto start = std::chrono::system_clock::now();
    try{
        graph = readAdjListFile(filename,firstVertex);
    }catch(std::exception& e){
        std::cerr << "Exception caught: " << e.what()<<std::endl;
        std::cout<<"Error reading file "<<filename<<". Exiting."
            <<std::endl;
        return 0;
    }
    
    if(argc == 3){
        firstVertex = atoi(argv[2]);
    }
    
    GraphAlgorithm* findShortPath = new Dijkstra();
    const std::map<int,Path>* paths;
    try{
        paths = (*findShortPath)(*graph,firstVertex);
    }catch(std::exception& e){
        std::cerr << "Exception caught: " << e.what()<<std::endl;
        std::cout<<"Invalid Start Vertex "<<filename<<". Exiting."
        <<std::endl;
        delete graph;
        delete findShortPath;
        return 0;
    }
    
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast
                <std::chrono::microseconds>(end - start);
    
    std::cout<<"Starting Vertex: "<<firstVertex<<std::endl;
    std::cout<<std::endl;
    std::cout<<*paths;
    std::cout<<"Elapsed Time: "<<elapsed.count();
    std::cout<<" microseconds"<<std::endl;
    
    delete findShortPath;
    delete paths;
    delete graph;
    
    return 0;
}

//Read adjacency list from file.
Graph* readAdjListFile(const std::string filename, int& startingVertex){
    std::ifstream file;
    file.open(filename);
    //guard if file fails to open...throw exception
    if(!file.is_open()){
        throw std::runtime_error("Failed to open file.");
    }
    
    int startVertex(0);
    int destVertex(0);
    int cost(0);
    std::string iLine = "";
    
    //number of vertices--read but unused
    std::getline(file, iLine);
    Graph* graph = new AdjacencyList_Graph();
    
    std::getline(file, iLine);
    std::stringstream sin(iLine);
    sin>>startVertex;
    //first vertex is our 'startingVertex', to find all paths from
    startingVertex = startVertex;
    sin>>destVertex;
    sin>>cost;
    graph->addEdge(startVertex,cost,destVertex);
    
    while(std::getline(file, iLine)){
        std::stringstream sin(iLine);
        sin>>startVertex;
        sin>>destVertex;
        sin>>cost;
        graph->addEdge(startVertex,cost,destVertex);
    }
    //check stream badbit state flag
    if (file.bad()) {
        //IO error
        throw std::runtime_error("Error reading data from stream cin.");
    }
    return graph;
}


