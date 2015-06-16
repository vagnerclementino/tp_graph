/*
 * TPGraph.h
 *
 *  Created on: 14/06/2015
 *      Author: vagner
 */

#ifndef TPGRAPH_H_
#define TPGRAPH_H_

#include <string>
#include <vector>
#include "../lib/TrabalhoPratico.h"

namespace PAA {

class TPGraph: public PAA::TrabalhoPratico {
private:

	//Definindo o número de argumentos do programa
	static const int NUMBER_OF_ARGUMENTS = 5;

	//Definindo a posição do nome do programa
	static const int PROGRAM_NAME_POSITION = 0;

	//Definindo a posição do arquivo de entrada do Grafo A
	static const int GRAPH_A_INPUT_FILE_POS = 1;

	//Definindo a posição do arquivo Sybil
	static const int GRAPH_A_SYBIL_FILE_POS = 2;

	//Definindo a posição do arquivo de entrada do Grafo A
	static const int GRAPH_B_INPUT_FILE_POS = 3;

	//Definindo a posição do arquivo Sybil
	static const int GRAPH_B_SYBIL_FILE_POS = 4;

	std::vector<std::string>* pProgArgs;//Armazena os argumentos do programa

	//Verifica se o atributo pProgArgs está valido
	const bool assertProgArgs(void)const;

	//@override Define o tempo final de execução
	void setFinalTime(void);

public:
	TPGraph(int, char**);
	virtual ~TPGraph();

	//@override
	void run(void);

	//@override
	void showUserMessage(const std::string&);

	//@override
	void showStatistics(void);

	//Retorna uma string com o nome do programa
	const std::string& getProgramName(void)const;

	//Retorna uma string com o nome do arquivo de entrada do Grafo A
	const std::string& getGraphAFileName(void)const;

	//Retorna uma string com o nome do arquivo de Sybil do Grafo A
	const std::string getGraphASybilName(void)const;

	//Retorna uma string com o nome do arquivo de entrada do Grafo
	const std::string& getGraphBFileName(void)const;

	//Retorna uma string com o nome do arquivo de Sybil do Grafo A
	const std::string& getGraphBSybilName(void)const;
};



} /* namespace PAA */

#endif /* TPGRAPH_H_ */
