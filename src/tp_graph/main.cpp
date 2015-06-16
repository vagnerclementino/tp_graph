/*
 * main.cpp
 *
 *  Created on: 24/01/2015
 *      Author: vagner
 */
#include "../lib/PAAException.h"
#include "TPGraph.h"
#include <cstdlib>


using namespace std;



int main(int argc, char **argv) {


    try {
       	PAA::TPGraph tp (argc,argv);
    	tp.run();
    	//Exibindo os dados da execução
    	tp.showStatistics();
    	exit(EXIT_SUCCESS);
	} catch (const PAA::PAAException& e) {
			e.printDebugMessage();
			exit(EXIT_FAILURE);
	}

}
