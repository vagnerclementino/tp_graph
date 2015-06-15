/*
 * Vertex.cpp
 *
 *  Created on: 14/06/2015
 *      Author: vagner
 */

#include "Vertex.h"
#include <sstream>

namespace PAA {

Vertex::Vertex(const std::string& vetexName) {

	this->name = vetexName;
	this->edges = this->arcs;
	this->previous = NULL;
	//Definindo valor padrão para os atributos
	this->resetData();

}

Vertex::Vertex(const Vertex &other){

	this->name = other.getName();
	this->arcs = other.arcs;
	this->edges = this->arcs;
	this->cost = other.getCost();
	this->visited = other.getVisited();
	this->previous = other.getPreviousVertex();
	this->color = other.getColor();

}
Vertex::~Vertex() {
	//Nada para fazer, não houve alocaçaõ dinâmcia de memória
}

void Vertex::resetData() {
    this->setCost(0.0);
    this->setPreviousVertex(NULL);
    this->setVisited(false);
    this->setColor(WHITE);

}

std::string Vertex::toString() const {
    std::ostringstream out;
    out << *this;
    return out.str();
}

Vertex& Vertex::operator =(const Vertex& other) {
    this->setName(other.getName());
    this->setEdges(other.getEdges());
    this->setCost(other.getCost());
    this->setVisited(other.getVisited());
    this->setPreviousVertex(other.getPreviousVertex());
    this->setColor(other.getColor());

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Vertex& v) {

    out << "Vertex{name=" << v.getName();
    out << ", cost=" << v.getCost();
    out << ", visited=" << (v.getVisited() ? "true" : "false");
    out << ", previous=" << (v.getPreviousVertex() == NULL ? std::string("NULL") : v.getPreviousVertex()->getName());

    out << ", neighbors={";
    int i = 0;
    for (Edge* edge : v.getEdges()) {
        if (i > 0) {
            out << ", ";
        }
        i++;
        if (edge->getFinishVertex() != NULL) {
            out << edge->getFinishVertex()->getName();
        } else {
            out << "NULL";
        }
    }
    out << "}";
    out << "}";
    return out;
}


std::string& Vertex::getName(void)const{

	return this->name;

}

void Vertex::setName(std::string& aName){

	this->name = aName;

}

double Vertex::getCost(void)const{

	return this->cost;
}

void Vertex::setCost(double aCost){

	this->cost = aCost;
}


bool Vertex::getVisited(void)const{

	return this->visited;

}

void Vertex::setVisited(bool aVisited){

	this->visited = aVisited;

}

//Métodos para acesso e alteração do atributo 'Color'
PAA::Color Vertex::getColor(void) const{

	return this->color;
}
void Vertex::setColor(PAA::Color newColor){

	this->color = newColor;

}

std::set<PAA::Edge*>& Vertex::getEdges(void) const{

	return this->edges;

}

void Vertex::setEdges(std::set<PAA::Edge*>& aEdgeSet){

	this->arcs = aEdgeSet;
}

//Métodos para acesso e alteração do atributo 'previous'
Vertex* Vertex::getPreviousVertex(void) const{

	return this->previous;

}

void Vertex::setPreviousVertex(Vertex* aVertice){

	this->previous = aVertice;
}



} /* namespace PAA */
