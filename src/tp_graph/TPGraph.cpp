/*
 * TPGraph.cpp
 *
 *  Created on: 14/06/2015
 *      Author: vagner
 */

#include "TPGraph.h"
#include <sstream>
#include <stdexcept>
#include "../lib/PAAException.h"
#include "../lib/TrabalhoPratico.h"
#include "PAAGraph.h"
#include <iostream>
#include "SybilFinder.h"

namespace PAA {

TPGraph::TPGraph(int numArgs, char** args):TrabalhoPratico(numArgs, args) {
	std::stringstream ss;
	if(numArgs == this->NUMBER_OF_ARGUMENTS){

		this->pProgArgs = new std::vector<std::string> (args, args + numArgs);

	}else{
		ss << "O numero de argumentos informado: "<< numArgs << " não é valido" << std::endl;
		throw PAA::PAAException(ss.str());

	}

}

TPGraph::~TPGraph() {
	if(this->pProgArgs != NULL){
		delete this->pProgArgs;
	}
}

const bool TPGraph::assertProgArgs(void) const{
	bool isValid;
	if (this->pProgArgs != NULL && this->pProgArgs->size() == this->NUMBER_OF_ARGUMENTS){
		isValid = true;
	}else{
		isValid = false;
	}
	return isValid;
}

const std::string& TPGraph::getGraphAFileName(void)const {
	std::stringstream ss;

	if( assertProgArgs()) {
		try {
			return this->pProgArgs->at(this->GRAPH_A_INPUT_FILE_POS);

		} catch (const std::out_of_range& oor) {
			ss<< "Erro em recuperar o nome do arquivo do Grafo A. Detalhes: " << oor.what() << std::endl;
			throw PAA::PAAException(ss.str());
		}

	}
	return NULL;
}

const std::string TPGraph::getGraphASybilName(void)const {
	std::stringstream ss;
	if( assertProgArgs()){
		try {
			return this->pProgArgs->at(this->GRAPH_A_SYBIL_FILE_POS);

		} catch (const std::out_of_range& oor) {
			ss<< "Erro em recuperar o nome do arquivo do Grafo A. Detalhes: " << oor.what() << std::endl;
			throw PAA::PAAException(ss.str());
		}

	}
	return NULL;
}

const std::string& TPGraph::getGraphBFileName(void)const {
	std::stringstream ss;
	if( assertProgArgs()){
		try {
			return this->pProgArgs->at(this->GRAPH_B_INPUT_FILE_POS);

		} catch (const std::out_of_range& oor) {
			ss<< "Erro em recuperar o nome do arquivo do Grafo A. Detalhes: " << oor.what() << std::endl;
			throw PAA::PAAException(ss.str());
		}

	}
	return NULL;
}

const std::string& TPGraph::getGraphBSybilName(void)const{
	std::stringstream ss;
	if( assertProgArgs()){
		try {

			return this->pProgArgs->at(this->GRAPH_B_SYBIL_FILE_POS);

		} catch (const std::out_of_range& oor) {
			ss<< "Erro em recuperar o nome do arquivo do Grafo A. Detalhes: " << oor.what() << std::endl;
			throw PAA::PAAException(ss.str());
		}

	}

	return NULL;
}

void TPGraph::showUserMessage(const std::string& message){
	PAA::TrabalhoPratico::showUserMessage(message);
}

void TPGraph::showStatistics(void){
	PAA::TrabalhoPratico::showStatistics();
}

void TPGraph::run(void){
	std::stringstream ss;
	const std::string graphARegionSybilFile = "regionSybilGA.txt";
	const std::string graphBSybilFile = "regionSybilGB.txt";
	const std::string graphAHonestFile = "regionHonestGA.txt";
	const std::string graphBHonestFile = "regionHonestGB.txt";
	const std::string graphAMetricsFile = "metricsGA.txt";
	const std::string graphBMetricsFile = "metricsGB.txt";

	std::string graphFilePath; //string do caminho dos dados dos grafos
	std::string graphSybilFile;	// string do caminho do arquivo texto dos dados dos sybil reais
	PAA::PAAGraph graphA;
	PAA::PAAGraph graphB;
	PAA::SybilFinder sybilFinder;
	try {

		this->showUserMessage("Iniciando a execução.");

		//Definindo os arquivos de saida
		graphA.setHonestRegionFileName(graphAHonestFile);
		graphA.setSybilRegionFileName(graphARegionSybilFile);
		graphA.setMetricsFileName(graphAMetricsFile);


		this->showUserMessage("Iniciando a verificação do GRAFO A.");

		//Definindo o arquivo de carga do GRAFO A
		graphFilePath = this->getGraphAFileName();

		//Definindo o arquivo Sybil para o GRAFO A
		graphSybilFile = this->getGraphASybilName();

		//Carregando os vértices e aresta do arquivo para o GRAFO A
		graphA.load(graphFilePath);

		//Carregando os arquivo dos Sybils Reais para o SybilFinder
		sybilFinder.loadSybilFile(graphSybilFile);

		//Localizando os Sybil para o GRAFO A
		sybilFinder.find(graphA);

		//Escrevendo os dados recuperados nos respectivos arquivos
		sybilFinder.writeHonestVertexSet(graphA.getHonestRegionFileName());
		sybilFinder.writeSybilVertexSet(graphA.getSybilRegionFileName());
		sybilFinder.writeMetrics(graphA.getMetricsFileName(), graphA);

		this->showUserMessage("Finalizando a verificação do GRAFO A.");

		/********************FIM GRAFO A**********************************/

		sybilFinder.resetData();

		/*********************INICIO GRAFO B****************************/
		this->showUserMessage("Iniciando a verificação do GRAFO B.");

		//Definindo os arquivos de saida
		graphB.setHonestRegionFileName(graphBHonestFile);
		graphB.setSybilRegionFileName(graphBSybilFile);
		graphB.setMetricsFileName(graphBMetricsFile);

		//Definindo o arquivo de carga do GRAFO A
		graphFilePath = this->getGraphBFileName();

		//Definindo o arquivo Sybil para o GRAFO A
		graphSybilFile = this->getGraphBSybilName();

		//Carregando os vértices e aresta do arquivo para o GRAFO A
		graphB.load(graphFilePath);

		//Carregando os arquivo dos Sybils Reais para o SybilFinder
		sybilFinder.loadSybilFile(graphSybilFile);

		//Localizando os Sybil para o GRAFO A
		sybilFinder.find(graphB);

		//Escrevendo os dados recuperados nos respectivos arquivos
		sybilFinder.writeHonestVertexSet(graphB.getHonestRegionFileName());
		sybilFinder.writeSybilVertexSet(graphB.getSybilRegionFileName());
		sybilFinder.writeMetrics(graphB.getMetricsFileName(), graphB);
		this->showUserMessage("Finalizando a verificação do GRAFO B.");


		this->showUserMessage(ss.str());
		this->showUserMessage("Finalizando a execução.");
		this->setFinalTime();

	} catch (const PAA::PAAException& e) {

		ss << "Erro durante a execução do programa: Detalhes: " << e.getDebugMessage() << std::endl;
		throw PAA::PAAException(ss.str());

	}


}



void TPGraph::setFinalTime(void){

	PAA::TrabalhoPratico::setFinalTime();

}


} /* namespace PAA */
