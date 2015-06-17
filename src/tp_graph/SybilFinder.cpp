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

const void SybilFinder::printRealSybilVertex(void)const {

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

const void SybilFinder::printSeedVertex(void) const{

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

					ss << (*it)->toString();

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

void SybilFinder::find(PAA::PAAGraph& graph){

	//Escolhendo aleatoriamente vértices como sementes
	std::set<PAA::Vertex*> seeds = this->chooseSeed(graph.getHonestSet());

	//Armazendo a sementes escolhidas
	this->setSeedsSet(seeds);

	this->printSeedVertex();


}
const std::set<PAA::Vertex*>& SybilFinder::getHonestVertexSet(void) const{

}
const std::set<PAA::Vertex*>& SybilFinder::getSybiltVertexSet(void) const{

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

