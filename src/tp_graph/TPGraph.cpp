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

namespace PAA {

TPGraph::TPGraph(int numArgs, char** args):TrabalhoPratico(numArgs, args) {
	std::stringstream ss;
	if(numArgs == this->NUMBER_OF_ARGUMENTS){

		this->pProgArgs = new std::vector<std::string> (args, args + this->NUMBER_OF_ARGUMENTS);

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

}

const std::string& TPGraph::getGraphASybilName(void)const {
	std::stringstream ss;
	if( assertProgArgs()){
		try {
			return this->pProgArgs->at(this->GRAPH_A_SYBIL_FILE_POS);

		} catch (const std::out_of_range& oor) {
			ss<< "Erro em recuperar o nome do arquivo do Grafo A. Detalhes: " << oor.what() << std::endl;
			throw PAA::PAAException(ss.str());
		}

	}

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

}

void TPGraph::showUserMessage(const std::string& message){
	PAA:TrabalhoPratico::showUserMessage(message);
}

void TPGraph::showStatistics(void){
	PAA::TrabalhoPratico::showStatistics();
}

void TPGraph::run(void){
	std::stringstream ss;

	try {
		this->showUserMessage("Iniciando a execução.");

		PAA::PAAGraph graph;

		graph.addVertex("1");
		this->showUserMessage(graph.getVertex("1")->toString());

		graph.addVertex("2");
		this->showUserMessage(graph.getVertex("2")->toString());

		graph.addEdge("1","2",1.0,false);

		ss << "Everything is gonna be alright" << std::endl;

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
