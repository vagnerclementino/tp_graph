/*
 * PAAGraph.cpp
 *
 *  Created on: 15/06/2015
 *      Author: vagner
 */

#include "PAAGraph.h"
#include <iostream>

namespace PAA {

/*
 * PAAGraph member implementations
 */
PAAGraph::PAAGraph() : PAA::Graph<Vertex, Edge>() {

	//Habilitando o reset dos dados de um grafo
    this->resetEnabled = true;
    this->fm = new PAA::FileManager();

}

//Destrutor não sera utilizado. Sem alocação dinâmica
PAAGraph::~PAAGraph(){

	delete this->fm;

}

void PAAGraph::clearEdges() {

	//Coletando as aretas as serem removidas.
    std::set<PAA::Edge*> edges = this->getEdgeSet();
    std::set<PAA::Edge*>::iterator itEdges;

    for (itEdges = edges.begin(); itEdges != edges.end(); itEdges++) {

        removeEdge(*itEdges);
    }
}

bool PAAGraph::containsEdge(Vertex* v1, Vertex* v2) const {

    return this->getEdge(v1, v2) != NULL;

}

bool PAAGraph::containsEdge(const std::string& v1, const std::string& v2) const {

    return this->getEdge(v1, v2) != NULL;
}

bool PAAGraph::containsEdge(Edge* edge) const {

	std::set<PAA::Edge*> edgeSet;
    if (edge == NULL) {
        return false;
    } else {

    	edgeSet = this->getEdgeSet();
    	return edgeSet.end() != edgeSet.find(edge);
    }
}



bool PAAGraph::containsVertex(const std::string& name) const {

    return this->getNode(name) != NULL;

}

bool PAAGraph::containsVertex(Vertex* v) const {

	std::set<PAA::Vertex*> vertexSet;
    if (v == NULL) {
        return false;
    } else {

    	vertexSet = this->getNodeSet();

    	return vertexSet.end() != vertexSet.find(v);

    }
}


Edge* PAAGraph::getEdge(Vertex* v1, Vertex* v2) const {

	std::set<PAA::Edge*>::iterator itEdges;

	for(itEdges = this->getEdgeSet(v1).begin(); itEdges != this->getEdgeSet(v1).end();itEdges++){
		if ( (*itEdges)->getFinishVertex() == v2){
			return (*itEdges);
		}
	}

    return NULL;
}

Edge* PAAGraph::getEdge(const std::string& v1, const std::string& v2) const {

    return this->getEdge(this->getVertex(v1), this->getVertex(v2));

}

Edge* PAAGraph::getInverseArc(Edge* edge) const {

    return this->getEdge(edge->getFinishVertex(), edge->getStartVertex());
}

Edge* PAAGraph::getInverseEdge(Edge* edge) const {

    return this->getInverseArc(edge);

}

bool PAAGraph::isNeighbor(const std::string& v1, const std::string& v2) const {
    return this->isNeighbor(this->getVertex(v1), this->getVertex(v2));
}

bool PAAGraph::isNeighbor(Vertex* v1, Vertex* v2) const {

	std::set<PAA::Edge*>::iterator itEdges;

	for(itEdges = this->getEdgeSet(v1).begin(); itEdges != this->getEdgeSet(v1).end();itEdges++){

		if( (*itEdges)->getFinishVertex() == v2){
			return true;
		}
	}
    return false;
}

void PAAGraph::resetData() {

	std::set<PAA::Edge*>::iterator itStartEdge;
	std::set<PAA::Edge*>::iterator itEndEdge;
	std::set<PAA::Edge*>::iterator itEdge;

	std::set<PAA::Vertex*>::iterator itStartVertex;
	std::set<PAA::Vertex*>::iterator itEndVertex;
	std::set<PAA::Vertex*>::iterator itVertex;

	itStartVertex = this->getVertexSet().begin();
	itEndVertex	  = this->getVertexSet().end();

	itStartEdge = this->getEdgeSet().begin();
	itEndEdge	= this->getEdgeSet().end();

    if (this->resetEnabled) {

    	for(itVertex = itStartVertex; itVertex != itEndVertex; itVertex++){

    		(*itVertex)->resetData();
    	}

    	for(itEdge = itStartEdge; itEdge != itEndEdge; itEdge++ ){

    		(*itEdge)->resetData();
    	}

    }
}

void PAAGraph::setResetEnabled(bool enabled) {

   this->resetEnabled = enabled;

}



Edge* PAAGraph::addEdge(const std::string& v1, const std::string& v2, double cost, bool directed) {

    return this->addEdge(getVertex(v1), getVertex(v2), cost, directed);

}

Edge* PAAGraph::addEdge(Vertex* v1, Vertex* v2, double cost, bool directed) {

    Edge* e = new Edge(v1, v2, cost);
    return addEdge(e, directed);

}

Edge* PAAGraph::addEdge(Edge* e, bool directed) {

    Edge* result = this->addArc(e);
    if (!directed) {

        Edge* result2 = this->addArc(e->getFinishVertex(), e->getStartVertex());

        result2->setWeight(e->getWeight());
    }
    return result;
}

Vertex* PAAGraph::addVertex(const std::string& name) {
    return this->addNode(name);
}

Vertex* PAAGraph::addVertex(Vertex* v) {
    return this->addNode(v);
}



Vertex* PAAGraph::setVertexAsHonest(const std::string& name){

	PAA::Vertex* honest;

	honest = this->getVertex(name);

	honest->setIsSybil(false);

	return honest;
}

Vertex* PAAGraph::setVertexAsSybil(const std::string& name){

	PAA::Vertex* sybil;

	sybil = this->getVertex(name);

	sybil->setIsSybil(true);

	return sybil;
}

const std::set<Edge*>& PAAGraph::getEdgeSet() const {
    return this->getArcSet();
}

const std::set<Edge*>& PAAGraph::getEdgeSet(Vertex* v) const {
    return this->getArcSet(v);
}

const std::set<Edge*>& PAAGraph::getEdgeSet(const std::string& v) const {
    return this->getArcSet(v);
}

Vertex* PAAGraph::getVertex(const std::string& name) const {
    return this->getNode(name);
}

const std::set<Vertex*>& PAAGraph::getVertexSet() const {
    return this->getNodeSet();
}

void PAAGraph::removeEdge(const std::string& v1, const std::string& v2, bool directed) {
    this->removeEdge(this->getVertex(v1), this->getVertex(v2), directed);
}

void PAAGraph::removeEdge(Vertex* v1, Vertex* v2, bool directed) {
    this->removeArc(v1, v2);
    if (!directed) {
        this->removeArc(v2, v1);
    }
}

void PAAGraph::removeEdge(Edge* e, bool directed) {
    this->removeArc(e);
    if (!directed) {
        this->removeArc(e->getFinishVertex(), e->getStartVertex());
    }
}

void PAAGraph::removeVertex(const std::string& name) {
    this->removeNode(name);
}

void PAAGraph::removeVertex(Vertex* v) {
    this->removeNode(v);
}


std::string PAAGraph::addToHonestSet(std::string& v){

	if(this->honestSet.size() < this->FIRSTS_HONESTS_VERTEX){

		this->honestSet.insert(v);
		return v;
	}else{
		return NULL;
	}
}

int PAAGraph::sizeHonestVertex(void){

	return this->honestSet.size();

}

std::set<PAA::Vertex*> PAAGraph::getHonestSet(){

	std::set<PAA::Vertex*> resultSet;
	std::set<std::string>::iterator it;

	for(it = this->honestSet.begin(); it != this->honestSet.end(); it++){

		resultSet.insert(this->getVertex((*it)));
	}

	return resultSet;
}

const std::string& PAAGraph::getHonestRegionFileName() const {
	return honestRegionFileName;
}

void PAAGraph::setHonestRegionFileName(
		const std::string& honestRegionFileName) {
	this->honestRegionFileName = honestRegionFileName;
}

const std::string& PAAGraph::getMetricsFileName() const {
	return metricsFileName;
}

void PAAGraph::setMetricsFileName(const std::string& metricsFileName) {
	this->metricsFileName = metricsFileName;
}

const std::string& PAAGraph::getSybilRegionFileName() const {
	return sybilRegionFileName;
}

void PAAGraph::setSybilRegionFileName(const std::string& sybilRegionFileName) {
	this->sybilRegionFileName = sybilRegionFileName;
}

void PAAGraph::printHonestSet(void) const{
	std::set<std::string>::iterator it;
		std::stringstream ss;
		int i = 0;

		if(this->honestSet.empty()){

			ss << "{ }" << std::endl;
		}else{

				ss << "{";

				for(it = this->honestSet.begin(); it != this->honestSet.end(); it++){
					if (i > 0) {
						ss << ", ";
					}
					i++;

					ss << (*it);

				}
				ss << "}";
		}
		std::cout << ss.str() << std::endl;
}
void PAAGraph::load(const std::string& filePath){

	 std::string line;
	 std::vector<std::string> valuesRead;
	 std::vector<std::string>::iterator itStr;
	 std::stringstream ss;
	 const char delimiter = ' ';
	 std::string vertexOriginName;
	 /*
	  * /Determina se o vértice carregado é o vertice fonte, ou seja, de
	  * onde sai as arestas
	  *
	  * */
	 bool isVertexSource = true;
	 int vertexHonestInserted = 0;//Total de vértices honesto inseridos até  o momento
	 PAA::Vertex* vertexAux;
	 PAA::Edge* edgeAux;

	 try {
		 this->fm->openFile(filePath,'R');
		 while(this->fm->hasMore()){

			 line = this->fm->readLine();
			 if(!line.empty()){

				//std::cout << line << " - " << line.size() << std::endl;


				//Copiando os valores lidos para o vector valuesRead
				valuesRead = this->fm->splitString(line.c_str(), delimiter);
				//std::cout << "Tamanho valores lido: " << valuesRead.size() << std::endl;

				for(itStr = valuesRead.begin(); itStr != valuesRead.end(); itStr++){

					if(isVertexSource){

						vertexOriginName = (*itStr);

						//
						if (vertexHonestInserted < this->FIRSTS_HONESTS_VERTEX) {

							//Inserido um vértice honesto
							this->addToHonestSet(vertexOriginName);
							vertexHonestInserted++;
							//std::cout << "Vertice Honesto Inserido" << vertexOriginName << std::endl;

						}

						if(!this->containsVertex(vertexOriginName)) {

							vertexAux = this->addVertex(vertexOriginName);

						}

						/*if (vertexAux) {


							std::cout << vertexAux->toString() << std::endl;

						}*/
						isVertexSource = false;
					}else{

						if (!this->containsVertex((*itStr))) {
							this->addVertex((*itStr));
						}
						//Incluíndo aresta entre os vértices
						edgeAux = this->addEdge(vertexOriginName, (*itStr), 1.0,true);
						/*if (edgeAux) {

							std::cout << edgeAux->toString() << std::endl;

						}*/

					}
				}

			 }

			 valuesRead.clear();
			 isVertexSource = true;

		 }

	 }catch (const std::exception& e) {

		 ss << "Erro ao ler o arquivo " << filePath << " Detalhes: " << e.what() << std::endl;

		 throw PAA::PAAException(ss.str());
	 }

}

} /* namespace PAA */
