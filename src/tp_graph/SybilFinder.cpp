/*
 * SybilFinder.cpp
 *
 *  Created on: 16/06/2015
 *      Author: vagner
 */

#include "SybilFinder.h"
#include <limits>
#include <set>
#include <iostream>
#include <math.h>
#include <cstdlib>


namespace PAA {


SybilFinder::SybilFinder() {

	this->honestVertex    =  std::set<PAA::Vertex*> ();
	this->sybilVertex     =  std::set<PAA::Vertex*> ();
	this->seeds        	  =  std::set<PAA::Vertex*> ();
	this->realSybilVertex =  std::set<std::string> ();
	this->fm			  =  new PAA::FileManager();
}

SybilFinder::~SybilFinder() {

	delete this->fm;

}

void SybilFinder::loadSybilFile(std::string& sybilFileName){

	std::string line;
	std::stringstream ss;

	try {

		this->fm->openFile(sybilFileName, 'R');

		while (this->fm->hasMore()) {

				line = this->fm->readLine();

				if (!line.empty()) {

					this->addRealSybilVertex(line);

				}
		}
	} catch (const std::exception& e) {

		ss << "Erro ao ler o arquivo " << sybilFileName << " Detalhes: " << e.what()
				<< std::endl;

		throw PAA::PAAException(ss.str());
	}
}

const void SybilFinder::printRealSybilVertexSet(void)const {

	std::set<std::string>::iterator it;
	std::stringstream ss;
	int i = 0;

	if(this->realSybilVertex.empty()){

		ss << "{ }" << std::endl;
	}else{

			ss << "{";

			for(it = this->realSybilVertex.begin(); it != this->realSybilVertex.end(); it++){
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

const void SybilFinder::printSeedVertexSet(void) const{

		std::set<PAA::Vertex*>::iterator it;
		std::stringstream ss;
		int i = 0;

		if(this->seeds.empty()){

			ss << "{ }" << std::endl;
		}else{

				ss << "{";

				for(it = this->seeds.begin(); it != this->seeds.end(); it++){
					if (i > 0) {
						ss << ", ";
					}
					i++;

					ss << (*it)->getName();

				}
				ss << "}";
		}
		std::cout << ss.str() << std::endl;

}

const void SybilFinder::printHonestVertexSet(void) const{

		std::set<PAA::Vertex*>::iterator it;
		std::stringstream ss;
		int i = 0;

		if(this->honestVertex.empty()){

			ss << "{ }" << std::endl;
		}else{

				ss << "{";

				for(it = this->honestVertex.begin(); it != this->honestVertex.end(); it++){
					if (i > 0) {
						ss << ", ";
					}
					i++;

					ss << (*it)->getName();

				}
				ss << "}";
		}
		std::cout << ss.str() << std::endl;

}


const void SybilFinder::printSybilVertexSet(void) const{

		std::set<PAA::Vertex*>::iterator it;
		std::stringstream ss;
		int i = 0;

		if(this->sybilVertex.empty()){

			ss << "{ }" << std::endl;
		}else{

				ss << "{";

				for(it = this->sybilVertex.begin(); it != this->sybilVertex.end(); it++){
					if (i > 0) {
						ss << ", ";
					}
					i++;

					ss << (*it)->getName();

				}
				ss << "}";
		}
		std::cout << ss.str() << std::endl;

}

const void SybilFinder::printCandidateVertexSet(std::set<PAA::Vertex*>& candidateVertex) const{

		std::set<PAA::Vertex*>::iterator it;
		std::stringstream ss;
		int i = 0;

		if (candidateVertex.empty()) {

			ss << "{ }" << std::endl;
		} else {

			ss << "{";

			for (it = candidateVertex.begin(); it != candidateVertex.end();
					it++) {
				if (i > 0) {
					ss << ", ";
				}
				i++;

				ss << (*it)->getName();

			}
			ss << "}";
		}
		std::cout << ss.str() << std::endl;

}

int SybilFinder::getSeedSize(int honestSetSize){

	int seedSize = 0;

	seedSize = (int) floor(this->SEED_PERCENT *  honestSetSize);

	return seedSize;
}

std::set<PAA::Vertex*> SybilFinder::chooseSeed(std::set<PAA::Vertex*>& candidateSet){

	int candidateSize = candidateSet.size();
	int seedSize = this->getSeedSize(candidateSize);
	std::set<PAA::Vertex*> seeds;
	std::vector<PAA::Vertex*> candidates;
	int randIndex;
	srand(time(0));

	if(!candidateSet.empty()  && seedSize > 0){



		//Copiando de set para vector
		std::copy(candidateSet.begin(), candidateSet.end(), std::back_inserter(candidates));

		//Criando um vetor para definir se a posicao i do vector candidates foi escolhida
		std::vector<bool> selected (candidates.size(),false);

		while(int(seeds.size()) < seedSize){

			randIndex = (rand() % candidateSize);

			if(!selected.at(randIndex)){

				seeds.insert(candidates.at(randIndex));
				selected.at(randIndex) = true;
			}


		}

}

	return seeds;
}

void SybilFinder::setSeedsSet(std::set<PAA::Vertex*>& seeds){

	this->seeds = seeds;

}

Vertex* SybilFinder::addToHonestSet(PAA::Vertex* v){


	this->honestVertex.insert(v);
	return v;

}

Vertex* SybilFinder::addToSybilSet(PAA::Vertex* v){

	this->sybilVertex.insert(v);
	return v;

}


std::set<PAA::Vertex*> SybilFinder::getSybilCandidates(std::set<PAA::Vertex*> graphVertexSet, std::set<PAA::Vertex*> seeds){

	std::set<PAA::Vertex*> candidates;
	std::set<PAA::Vertex*>::iterator it;

	for(it = graphVertexSet.begin(); it != graphVertexSet.end(); it++){

		if(seeds.find((*it)) == seeds.end()){
			//Vertíce não foi encontrado poderá ser inserido
			candidates.insert((*it));
		}

	}

	return candidates;

}

float SybilFinder::calculeCondutanciaNorm(PAA::PAAGraph& graph){

	std::set<PAA::Vertex*>::iterator it;

	//Numero de aresta entre vertíces no conjunto honesto (Conjunto A)
	int edgesAA = 0;

	//Numero de aresta entre vertíces no conjunto honesto (A) e no conjunto (B)
	int edgesAB = 0;

	//Numero de aresta entre vertíces no conjunto sybil (b)
	int edgesBB = 0;

	//Valore sem float para realizar os cálculos
	float fEdgesAA;
	float fEdgesAB;
	float fEdgesBB;


	float condutanciaNormailizada = 0.0;

	float graphCondutancia = 0.0;

	float valorEsperadoK = 0.0;


	for(it = graph.getVertexSet().begin(); it != graph.getVertexSet().end(); it++){

			edgesAA += (*it)->getNumberEdgesAA();
			edgesAB += (*it)->getNumberEdgesAB();
			edgesBB += (*it)->getNumberEdgesBB();
	}


	fEdgesAA = float (edgesAA);

	fEdgesAB = float (edgesAB);

	fEdgesBB = float (edgesBB);


	graphCondutancia =  (  ( fEdgesAA ) / ( fEdgesAA + fEdgesAB) );


	valorEsperadoK = ( ( (fEdgesAA + fEdgesAB) * (fEdgesBB + fEdgesAB)) / ( ( (fEdgesAA + fEdgesAB) * (fEdgesAA + fEdgesAB) ) + ((fEdgesAA + fEdgesAB) * (fEdgesBB + fEdgesAB)) ));

	condutanciaNormailizada = graphCondutancia - valorEsperadoK;



	return condutanciaNormailizada;

}

void SybilFinder::find(PAA::PAAGraph& graph){

	//Escolhendo aleatoriamente vértices como sementes
	std::set<PAA::Vertex*> seeds = this->chooseSeed(graph.getHonestSet());//Conjunto A
	std::set<PAA::Vertex*> sybilCandidates; // Conjuntno B = (V-A)
	std::set<PAA::Vertex*>::iterator it;
	float actualConduntanciaNorm = 0.0; //Coduntância Normalizada antes de  testar um vértice v como honesto
	float newConduntanciaNorm = 0.0; //Condutância Normalizada apos testar um vértice v como honesto



	//Adicionando as sementes para o conjuto honesto (conjunto A)
	for(it = seeds.begin(); it != seeds.end(); it++){

		this->addToHonestSet(*(it));

	}

	//Armazenando as sementes
	this->setSeedsSet(seeds);

	this->printSeedVertexSet();

	//Recuperando os candidados C = V - S, onde S são as sementes
	sybilCandidates = this->getSybilCandidates(graph.getVertexSet(),seeds);

	this->printCandidateVertexSet(sybilCandidates);

	//Definindo as sementes como honestas
	for(it = seeds.begin(); it != seeds.end(); it++){

		graph.setVertexAsHonest((*it)->getName());

	}

	actualConduntanciaNorm = this->calculeCondutanciaNorm(graph);


	for(it = sybilCandidates.begin(); it != sybilCandidates.end(); it++){

		std::cout << "Vértice avaliado: " << (*it)->toString() << std::endl;

		graph.setVertexAsHonest((*it)->getName());

		newConduntanciaNorm = this->calculeCondutanciaNorm(graph);

		std::cout << "Nova Condutância: " << newConduntanciaNorm << std::endl;

		if(newConduntanciaNorm > actualConduntanciaNorm){

			//O Vértice será considerado como honesto
			this->addToHonestSet((*it));
			actualConduntanciaNorm = newConduntanciaNorm;

		}else{
			//O vértice será considerado como sybil

			//Desfazendo a tentativa de que o grafo era honesto
			graph.setVertexAsSybil((*it)->getName());
			this->addToSybilSet((*it));

		}

	}










}
const std::set<PAA::Vertex*>& SybilFinder::getHonestVertexSet(void) const{

	return this->honestVertex;

}

const std::set<PAA::Vertex*>& SybilFinder::getSybiltVertexSet(void) const{


	return this->sybilVertex;


}

void SybilFinder::addRealSybilVertex(std::string& sybil){

	std::stringstream ss;
	try{

		this->realSybilVertex.insert(sybil);
	}catch (const std::exception& e){

		ss << "Erro ao inserir o vértice " << sybil << " Detalhes: " << e.what()
						<< std::endl;

				throw PAA::PAAException(ss.str());
	}


}

} /* namespace PAA */

