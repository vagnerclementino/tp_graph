/*
 * Vertex.cpp
 *
 *  Created on: 14/06/2015
 *      Author: vagner
 */

#include "Vertex.h"
#include <sstream>
#include "../lib/PAAException.h"

namespace PAA {

Vertex::Vertex(const std::string& vetexName):edges(arcs) {

	this->name = vetexName;
	this->previous = NULL;
	//Definindo valor padrão para os atributos
	this->resetData();

}

Vertex::Vertex(const Vertex &other): edges(arcs){

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

	std::set<PAA::Edge*> edges;
	std::set<PAA::Edge*>::iterator itEdges;
    out << "Vertex{name=" << v.getName();
    out << ", cost=" << v.getCost();
    out << ", visited=" << (v.getVisited() ? "true" : "false");
    out << ", previous=" << (v.getPreviousVertex() == NULL ? std::string("NULL") : v.getPreviousVertex()->getName());

    out << ", neighbors={";
    int i = 0;

    edges = v.getEdges();

    for(itEdges = edges.begin(); itEdges != edges.end(); itEdges++) {

        if (i > 0) {
            out << ", ";
        }
        i++;

        if ( (*itEdges)->getFinishVertex() != NULL) {
            out << (*itEdges)->getFinishVertex()->getName();
        } else {
            out << "NULL";
        }
    }
    out << "}";
    out << "}";
    return out;
}


const std::string& Vertex::getName(void)const{

	return this->name;

}

void Vertex::setName(const std::string& aName){

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

//Adiciona um um aresta para um vértice
PAA::Edge* Vertex::addEdges(PAA::Edge* edge){
	std::stringstream ss;
	try {

		this->arcs.insert(edge);

	} catch (const std::exception& e) {

		ss << "Erro ao inserir a aresta " << edge->toString() << ". Detalhes:  "<< e.what() << std::endl;

		throw PAA::PAAException(ss.str());

	}
	this->arcs.insert(edge);

	return edge;

}

//Remove uma aresta de vértice
PAA::Edge* Vertex::removeEdge(PAA::Edge* edge){

}

} /* namespace PAA */
