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
#include <algorithm>


namespace PAA {


SybilFinder::SybilFinder() {

	this->honestVertex    =  std::set<PAA::Vertex*> ();
	this->sybilVertex     =  std::set<PAA::Vertex*> ();
	this->seeds        	  =  std::set<PAA::Vertex*> ();
	this->realSybilVertex =  std::set<std::string> ();
	this->honestRegionFile = new PAA::FileManager();
	this->sybilRegionFile = new PAA::FileManager();
	this->metricFile	  = new PAA::FileManager();
	this->fm 		      = new PAA::FileManager();
}

SybilFinder::~SybilFinder() {


	delete this->honestRegionFile;
	delete this->sybilRegionFile;
    delete this->metricFile;
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

const void SybilFinder::printCandidateVertexSet(std::vector<PAA::Vertex*>& candidateVertex) const{

		std::vector<PAA::Vertex*>::iterator it;
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

int SybilFinder::getSeedSize(void){

	return this->NUMBER_OF_SEED;
}

std::set<PAA::Vertex*> SybilFinder::chooseSeed(std::set<PAA::Vertex*> candidateSet){

	int candidateSize = candidateSet.size();
	int seedSize = this->getSeedSize();
	std::set<PAA::Vertex*> seeds;
	std::vector<PAA::Vertex*> candidates;
	std::set<PAA::Vertex*>::iterator it;
	int randIndex;
	srand(time(0));

	try {

		if(!candidateSet.empty()  && seedSize > 0){



			//Copiando de set para vector
			for(it = candidateSet.begin(); it != candidateSet.end(); it++){

				candidates.push_back((*it));
			}

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

	} catch (const std::exception& e) {

		std::cout << e.what() << std::endl;


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


std::vector<PAA::Vertex*> SybilFinder::getSybilCandidates(std::set<PAA::Vertex*> graphVertexSet, std::set<PAA::Vertex*> seeds){

	std::vector<PAA::Vertex*> candidates;
	std::set<PAA::Vertex*>::iterator it;

	for(it = graphVertexSet.begin(); it != graphVertexSet.end(); it++){

		if(seeds.find((*it)) == seeds.end()){
			//Vertíce não foi encontrado poderá ser inserido
			candidates.push_back((*it));
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
	float fEdgesAA = 0.0;
	float fEdgesAB = 0.0;
	float fEdgesBB = 0.0;


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


	valorEsperadoK = ( ( (edgesAA + edgesAB) * (edgesBB + edgesAB)) / ( ( (edgesAA + edgesAB) * (edgesAA + edgesAB) ) + ((edgesAA + edgesAB) * (edgesBB + edgesAB)) ));

	//std::cout << "Condutancia: " << graphCondutancia << std::endl;

	//std::cout << "Valor Esperado: " << valorEsperadoK << std::endl;

	condutanciaNormailizada = graphCondutancia - valorEsperadoK;



	return condutanciaNormailizada;

}

void SybilFinder::find(PAA::PAAGraph& graph){

	//Escolhendo aleatoriamente vértices como sementes
	std::set<PAA::Vertex*> seeds = this->chooseSeed(graph.getHonestSet());//Conjunto A
	std::vector<PAA::Vertex*> sybilCandidates; // Conjuntno B = (V-A)
	std::set<PAA::Vertex*>::iterator it;
	std::vector<PAA::Vertex*>::iterator itVector;
	float actualConduntanciaNorm = 0.0; //Coduntância Normalizada antes de  testar um vértice v como honesto
	float newConduntanciaNorm = 0.0; //Condutância Normalizada apos testar um vértice v como honesto



	//Adicionando as sementes para o conjuto honesto (conjunto A)
	for(it = seeds.begin(); it != seeds.end(); it++){

		this->addToHonestSet(*(it));

	}

	//Armazenando as sementes
	this->setSeedsSet(seeds);

	//this->printSeedVertexSet();

	//Recuperando os candidados C = V - S, onde S são as sementes
	sybilCandidates = this->getSybilCandidates(graph.getVertexSet(),seeds);

	//this->printCandidateVertexSet(sybilCandidates);



	//Definindo as sementes como honestas
	for(it = seeds.begin(); it != seeds.end(); it++){

		graph.setVertexAsHonest((*it)->getName());

	}

	actualConduntanciaNorm = this->calculeCondutanciaNorm(graph);

	//std::cout << "Condutancia Inicial:  " << actualConduntanciaNorm << std::endl;

	for(itVector = sybilCandidates.begin(); itVector != sybilCandidates.end(); itVector++){

		//std::cout << "Vértice avaliado: " << (*itVector)->toString() << std::endl;

		graph.setVertexAsHonest((*itVector)->getName());

		newConduntanciaNorm = this->calculeCondutanciaNorm(graph);

		//std::cout << "Nova Condutância: " << newConduntanciaNorm << std::endl;

		if(newConduntanciaNorm > actualConduntanciaNorm){

			//O Vértice será considerado como honesto
			this->addToHonestSet((*itVector));
			actualConduntanciaNorm = newConduntanciaNorm;

		}else{
			//O vértice será considerado como sybil

			//Desfazendo a tentativa de que o grafo era honesto
			graph.setVertexAsSybil((*itVector)->getName());
			this->addToSybilSet((*itVector));

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

float SybilFinder::calculeMedianDegree(PAA::PAAGraph& graph){
	int counter = 0;
	int degreeSum =0;
	float median;

	std::set<PAA::Vertex*>::iterator it;

	for(it = graph.getVertexSet().begin(); it != graph.getVertexSet().end(); it++){


		degreeSum += (*it)->getDegree();
		counter++;


	}



	median = float(degreeSum) / float (counter);

	return median;

}

float SybilFinder::calculeModularity(PAA::PAAGraph& graph){

	float modularity = 0.0;

	std::set<PAA::Vertex*>::iterator it;

    int edgesAA, edgesAB, edgesBB, edgesBA, totalEgdes;

	float fEdgesAA = 0.0;
	float fEdgesAB = 0.0;
	float fEdgesBB = 0.0;
	float fEdgesBA = 0.0;

	float condutanciaNormailizada = 0.0;

	float graphCondutancia = 0.0;

	float valorEsperadoK = 0.0;

	totalEgdes = 0;

	for (it = graph.getVertexSet().begin(); it != graph.getVertexSet().end();
			it++) {
		totalEgdes += (*it)->getDegree();
		edgesAA += (*it)->getNumberEdgesAA();
		edgesAB += (*it)->getNumberEdgesAB();
		edgesBB += (*it)->getNumberEdgesBB();
		edgesBA += (*it)->getNumberEdgesBA();
	}
	fEdgesAA = float(edgesAA);

	fEdgesAB = float(edgesAB);

	fEdgesBB = float(edgesBB);

	fEdgesBA = float(edgesBA);

	modularity = ( (fEdgesAA + fEdgesBB) / float (totalEgdes) ) -
				pow((float (fEdgesAA/totalEgdes)),2.0) +
				pow((float (fEdgesAB/totalEgdes)),2.0) +
				pow((float (fEdgesBB/totalEgdes)),2.0) +
				pow((float (fEdgesBA/totalEgdes)),2.0);
	return modularity;

}

float SybilFinder::calculeHonestCondutancia(const std::set<PAA::Vertex*>& vertexSet){


		std::set<PAA::Vertex*>::iterator it;

	    int edgesAA, edgesAB;

		float fEdgesAA = 0.0;
		float fEdgesAB = 0.0;
		float setCondutancia = 0.0;





		for (it = vertexSet.begin(); it != vertexSet.end();
				it++) {

			edgesAA += (*it)->getNumberEdgesAA();
			edgesAB += (*it)->getNumberEdgesAB();


		}
		fEdgesAA = float(edgesAA);
		fEdgesAB = float(edgesAB);





		setCondutancia = (fEdgesAB / fEdgesAA);
		return setCondutancia;


}

float SybilFinder::calculeSybilCondutancia(const std::set<PAA::Vertex*>& vertexSet){


		std::set<PAA::Vertex*>::iterator it;

	    int edgesBB, edgesAB;

		float fEdgesBB = 0.0;
		float fEdgesAB = 0.0;
		float setCondutancia = 0.0;
		for (it = vertexSet.begin(); it != vertexSet.end();it++) {

			edgesBB += (*it)->getNumberEdgesBB();
			edgesAB += (*it)->getNumberEdgesAB();

		}
		fEdgesBB = float(edgesBB);
		fEdgesAB = float(edgesAB);

		setCondutancia = (fEdgesAB / fEdgesBB);
		return setCondutancia;
}

float SybilFinder::calculeClusteringCoefficient(const std::set<PAA::Vertex*>& vertexSet){

	std::set<PAA::Vertex*>::iterator it;
	float clusteringCoefficient = 0.0;
	int counter = 0;

	for (it = vertexSet.begin(); it != vertexSet.end(); it++) {

		counter++;
		clusteringCoefficient += (*it)->getCusteringCoefficient();

	}
	if(counter == 0){

		return 0.0;

	}else{

		return float (clusteringCoefficient) / float (counter);

	}


}

float SybilFinder::calculeSybilRightFraction(const std::set<PAA::Vertex*>& sybilSet, const std::set<std::string>& sybilRealSet){

	std::set<PAA::Vertex*>::iterator it;
	int totalSybilRealSet = sybilRealSet.size();
	float sybilRightFraction = 0.0;
	int sybilRightCounter = 0;

	for (it = sybilSet.begin(); it != sybilSet.end(); it++){

		if(sybilRealSet.find((*it)->getName()) != sybilRealSet.end()){
			//Encontrado
			sybilRightCounter++;
		}
	}

    if(totalSybilRealSet == 0){

    	sybilRightFraction = 0.0;

    }else{

    	sybilRightFraction = ( float (sybilRightCounter) / float (totalSybilRealSet) );
	}


	return sybilRightFraction;

}

float SybilFinder::calculeHonestRightFraction(const std::set<PAA::Vertex*>& honestSet, const std::set<std::string>& sybilRealSet) {

	std::set<PAA::Vertex*>::iterator it;
	int totalSybilRealSet = sybilRealSet.size();
	float honestRightFraction = 0.0;
	int honestRightCounter = 0;

	for (it = honestSet.begin(); it != honestSet.end(); it++) {


		if (sybilRealSet.find((*it)->getName()) == sybilRealSet.end()) {
			//Não Encontrado
			honestRightCounter++;
		}
	}

	if (totalSybilRealSet == 0) {

		honestRightFraction = 0.0;

	} else {

		honestRightFraction = (float(honestRightCounter)
				/ float(totalSybilRealSet));
	}

	return honestRightFraction;

}

float SybilFinder::calculeFalsePositive(const std::set<PAA::Vertex*>& sybilSet, const std::set<std::string>& realSybilSet){

	float falsePositive = 0.0;
	int counter = 0;
	int sybilSetLength = sybilSet.size();
	std::set<PAA::Vertex*>::iterator it;

	for(it = sybilSet.begin(); it != sybilSet.end(); it++){

		if(realSybilSet.find((*it)->getName()) == realSybilSet.end()){

			counter++;

		}
	}

	if (sybilSetLength == 0){

		falsePositive = 0.0;
	}else{

		falsePositive =  ( float (counter) / float (sybilSetLength) );
	}

	return falsePositive;
}

float SybilFinder::calculeFalseNegative(const std::set<PAA::Vertex*>& honestSet, const std::set<std::string>& realSybilSet){

	float falseNegative = 0.0;
	int counter = 0;
	int honestSetSetLength = honestSet.size();
	std::set<PAA::Vertex*>::iterator it;

	for(it = honestSet.begin(); it != honestSet.end(); it++){


		if( realSybilSet.find((*it)->getName()) != realSybilSet.end()){
			counter++;

		}
	}

	if(honestSetSetLength == 0){

		falseNegative = 0.0;
	}else{

		falseNegative = ( float (counter) / float (honestSetSetLength) );

	}

	return falseNegative;
}

void SybilFinder::writeHonestVertexSet(const std::string& fileName){

	std::stringstream ss;
	std::vector<Vertex*>::iterator it;
	std::vector<PAA::Vertex*> outputVector;
	this->openRegionHonestFile(fileName);

	this->copySetToVector(outputVector,this->getHonestVertexSet());

	std::sort(outputVector.begin(),outputVector.end(), sortByName);

	for(it = outputVector.begin(); it != outputVector.end(); it++){

		ss << (*it)->getName() << std::endl;
	}

	this->writeToRegionHonestFile(ss.str());


    this->closeRegionHonestFile();
}

void SybilFinder::closeRegionSybilFile(void){

	try {

		this->closeFile(this->sybilRegionFile);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}

}

void SybilFinder::closeRegionHonestFile(void){

	try {

		this->closeFile(this->honestRegionFile);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}

}

void SybilFinder::writeSybilVertexSet(const std::string& fileName){

	std::stringstream ss;
	std::vector<Vertex*>::iterator it;
	std::vector<PAA::Vertex*> outputVector;
	this->openRegionSybilFile(fileName);

	this->copySetToVector(outputVector, this->getSybiltVertexSet());

	std::sort(outputVector.begin(), outputVector.end(), sortByName);

	for (it = outputVector.begin(); it != outputVector.end(); it++) {

		ss << (*it)->getName() << std::endl;
	}

	this->writeToRegionSybilFile(ss.str());

	this->closeRegionSybilFile();


}

void SybilFinder::writeMetrics(const std::string& fileName, PAA::PAAGraph& graph){

	std::stringstream ss;

	try {
		this->openMetricFile(fileName);

		//(a) grau médio dos vértices;
		ss << this->calculeMedianDegree(graph) << std::endl;

		//(b) modularidade;
		ss << this->calculeModularity(graph) << std::endl;

		//(c) condutância da região Sybil;
		ss << this->calculeSybilCondutancia(this->getSybiltVertexSet()) << std::endl;

		//(d) condutância da região honesta;
		ss << this->calculeHonestCondutancia(this->getHonestVertexSet()) << std::endl;

		//(e) coeficiente de agrupamento da região Sybil;
		ss << this->calculeClusteringCoefficient(this->getSybiltVertexSet()) << std::endl;;

		//(f) coeficiente de agrupamento da região honesta;
		ss << this->calculeClusteringCoefficient(this->getHonestVertexSet()) << std::endl;;

		//(g) fração de vértices Sybil corretamente classificados;
		ss << this->calculeSybilRightFraction(this->getSybiltVertexSet(), this->getRealSybilVertex()) << std::endl;;

		//(h) fração de vértices honestos corretamente classificados;
		ss << this->calculeHonestRightFraction(this->getHonestVertexSet(), this->getRealSybilVertex()) << std::endl;;

		//(i) fração de falsos positivos (vértices honestos identificados de forma incorreta como Sybil);
		ss << this->calculeFalsePositive(this->getSybiltVertexSet(), this->getRealSybilVertex()) << std::endl;;

		//(j) fração de falsos negativos (vértices Sybil identificados de forma incorreta como honestos).
		ss << this->calculeFalseNegative(this->getHonestVertexSet(), this->getRealSybilVertex()) << std::endl;;

		//Escreve para o arquivo
		this->writeToFile(ss.str(), this->metricFile);

		this->closeMetricFile();

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}



}

void SybilFinder::openRegionHonestFile(const std::string& fileName){

	try {

		this->openFile(fileName, this->honestRegionFile);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}


}

void SybilFinder::openRegionSybilFile(const std::string& fileName){

	try {

			this->openFile(fileName, this->sybilRegionFile);

		} catch (const PAA::PAAException& e) {

			throw new PAA::PAAException(e.getDebugMessage());
		}


}

void SybilFinder::writeToRegionHonestFile(const std::string& text){

	try {

		this->writeToFile(text,this->honestRegionFile);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}

}

void SybilFinder::writeToRegionSybilFile(const std::string& text){

	try {

		this->writeToFile(text,this->sybilRegionFile);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}

}

void SybilFinder::resetData(void){

	this->honestVertex.clear();
	this->realSybilVertex.clear();
	this->seeds.clear();
	this->sybilVertex.clear();
}

void SybilFinder::copySetToVector(std::vector<PAA::Vertex*>& destVector, const std::set<PAA::Vertex*>& sourceSet){

	std::copy(sourceSet.begin(), sourceSet.end(), std::back_inserter(destVector));


}

void SybilFinder::closeFile(PAA::FileManager* fm){

	try {

		fm->closeFile();

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}

}

void SybilFinder::writeToFile(const std::string& text, PAA::FileManager* fm){

	try {

		fm->writeToFile(text);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}


}

void SybilFinder::openFile(const std::string& fileName,	PAA::FileManager* fm){

	try {

		fm->openFile(fileName, 'W');

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}

}

void SybilFinder::openMetricFile(const std::string& fileName){

	try {

		this->openFile(fileName, this->metricFile);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}
}

void SybilFinder::closeMetricFile(void){

	try {

		this->closeFile(this->metricFile);

	} catch (const PAA::PAAException& e) {

		throw new PAA::PAAException(e.getDebugMessage());
	}


}

} /* namespace PAA */

const std::set<std::string>& PAA::SybilFinder::getRealSybilVertex() const {
	return realSybilVertex;
}

void PAA::SybilFinder::setRealSybilVertex(
		const std::set<std::string>& realSybilVertex) {
	this->realSybilVertex = realSybilVertex;
}
