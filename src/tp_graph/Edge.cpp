/*
 * Edge.cpp
 *
 *  Created on: 14/06/2015
 *      Author: vagner
 */

#include "Edge.h"
#include <sstream>

namespace PAA {

Edge::Edge(Vertex* start, Vertex* finish, double cost): weight(cost){
	this->setStartVertex(start);
	this->setFinishVertex(finish);
	this->setWeight(cost);
	this->setVisited(false);
	this->cost = cost;
	//this->weight = this->cost;
    this->resetData();
}

Edge::~Edge() {
    //Nada a ser feito. Não há alocação dinâmica de memória
}

void Edge::resetData() {
    this->visited = false;
}

std::string Edge::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

Edge& Edge::operator =(const Edge& other) {

    this->setStartVertex(other.getStartVertex());
    this->setFinishVertex(other.getFinishVertex());
    this->setWeight(other.getWeight());
    this->setVisited(other.getVisited());
    return *this;
}


std::ostream& operator<<(std::ostream& out, const PAA::Edge& edge) {

    out << "Edge{start=";
    if (edge.getStartVertex() == NULL) {
        out << "NULL";
    } else {
        out << edge.getStartVertex()->getName();
    }
    out << ", finish=";
    if (edge.getFinishVertex() == NULL) {
        out << "NULL";
    } else {
        out << edge.getFinishVertex()->getName();
    }
    if (edge.getWeight() != 0.0) {
        out << ", weight=" << edge.getWeight();
    }
    if (edge.getVisited()) {
        out << ", visited=" << (edge.getVisited() ? "true" : "false");
    }
    out << "}";
    return out;
}

} /* namespace PAA */


