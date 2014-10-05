/**
 @file paths.cpp
 Author         Ken Zyma (kzyma650)\n
 Creation:      Date: Oct. 1, 2014\n
 Due Date:      Oct. 8, 2014\n
 Courses:       CSC402\n
 Professor:     Dr. Speigel\n
 Assignment:    Project 2\n
 Filename:      paths.cpp\n
 
 
 */

#include "paths.h"

/* Path */
Path::Path(const int endVertex):cost(INT_MAX),endVertex(endVertex),
marked(false){}

Path& Path::operator=(const Path& rhs){
    if(this == &rhs){return *this;}
    this->cost = rhs.getCost();
    this->path = rhs.getPath();
    this->endVertex = rhs.getEndVertex();
    this->marked = rhs.isMarked();
    return *this;
}

void Path::setCost(const int cost){
    this->cost = cost;
}

int Path::getCost()const{
    return this->cost;
}

void Path::setPath(const std::vector<int> path){
    this->path = path;
}

std::vector<int> Path::getPath()const{
    return this->path;
}

void Path::addToPath(const int vertex){
    this->path.push_back(vertex);
}

int Path::getEndVertex()const{
    return this->endVertex;
}

bool Path::isMarked()const{
    return this->marked;
}

void Path::markVertex(){
    this->marked = true;
}

int Path::size(){
    return this->path.size();
}

int Path::at(int index){
    return this->path.at(index);
}

/* Path - nonmember functions */
bool operator < (const Path &p1,const Path &p2){
    return (p1.getCost() < p2.getCost());
}

bool operator > (const Path &p1,const Path &p2){
    return (p1.getCost() > p2.getCost());
}

bool Path_GreaterCompare::operator()
(const Path* a, const Path* b){
    return (*a > *b);
}

std::ostream& operator<<(std::ostream& os, const Path& path){
    os<<"End Vertex: "<<path.getEndVertex()<<"\n";
    os<<"Cost:"<<path.getCost()<<"\n";
    os<<"Path:"<<"\n";
    std::vector<int> p = path.getPath();
    for(int i=0;i<p.size();i++){
        os<<p.at(i)<<" ";
    }
    os<<"\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::map<int,Path> paths){
    for(auto it=paths.begin(); it != paths.end(); it++) {
        os<<"Ending Vertex: "<<it->first<<std::endl;
        Path curPath = it->second;
        os<<"Cost: "<<curPath.getCost()<<std::endl;
        os<<"Path: "<<std::endl;
        for(auto i=0;i<curPath.size();i++){
            os<<curPath.at(i)<<" ";
        }
        os<<std::endl;
        os<<std::endl;
    }
    return os;
}

/* GraphAlgorithm */
GraphAlgorithm::~GraphAlgorithm(){}

/* Dijkstra */
Dijkstra::~Dijkstra(){}

const std::map<int,Path>*  Dijkstra::operator()
(const Graph &graph,const int startVertex)const{
    
    if(!graph.isInGraph(startVertex)){
        throw std::runtime_error("Failed to open file.");
    }
    
    std::map<int,Path>* shortPath = new std::map<int,Path>();
    std::map<int,Path>* relaxedPath = new std::map<int,Path>();
    std::priority_queue<Path*,std::vector<Path*>,Path_GreaterCompare > pQueue;
    
    //fill relaxedPath with default path's (path cost == inf)
    std::vector<int> vertices = graph.getVertices();
    for(auto i=0;i<vertices.size();i++){
        Path p(vertices.at(i));
        relaxedPath->insert(std::pair<int,Path>(vertices.at(i),p));
    }
    relaxedPath->at(startVertex).setCost(0);
    relaxedPath->at(startVertex).addToPath(startVertex);
    pQueue.push(&(relaxedPath->at(startVertex)));
    
    while(!pQueue.empty()){
        /*************************************************************
         * make_heap is not called when p_queue.top() is called, thus
         * if a cost was changed indirectly (below when updating
         * adjacent vertices) the heap property will no longer hold
         * and the priority queue may perform unexpecedly. Becuase of
         * this two options are possible:
         * 1) subclass std::priority_queue and make sure make_heap is
         * called when an object is topp'ed, or
         * 2) use an incredibly hackish workaround
         * ...I choose the latter. Although 'hackish', this will work
         * anytime the underlying container is a std::vector, since vectors
         * are garenteed to be stored in contigous memory.
         */
        std::make_heap(const_cast<Path**>(&pQueue.top()),
                       const_cast<Path**>(&pQueue.top()) + pQueue.size(),
                       Path_GreaterCompare());
        /***************************************************************/
        Path* curPath = pQueue.top();
        pQueue.pop();
        int curVertex = curPath->getEndVertex();
        curPath->markVertex();
        //if vertex is marked, its lowest cost is found...
        //add to shortPath map for return.
        shortPath->insert(std::pair<int,Path>(curVertex,*curPath));
        auto adjVertices = graph.getAdjacent(curVertex);
        for(auto i=0;i<adjVertices.size();i++){
            Edge adjE = adjVertices.at(i);
            int newCost = curPath->getCost() + adjE.cost;
            int adjV = adjE.destinationVertex;
            if(newCost < (relaxedPath->at(adjV)).getCost()){
                auto newPath = curPath->getPath();
                newPath.push_back(adjV);
                relaxedPath->at(adjV).setPath(newPath);
                relaxedPath->at(adjV).setCost(newCost);
                pQueue.push(&(relaxedPath->at(adjV)));
            }
            //if not marked and newCost is lower, update path
        }
    }
    delete relaxedPath;
    return shortPath;
}


