/*
 * SybilFinder.h
 *
 *  Created on: 16/06/2015
 *      Author: vagner
 */

#ifndef SYBILFINDER_H_
#define SYBILFINDER_H_
#include "../lib/PAAException.h"
#include "Vertex.h"
#include "Edge.h"
#include "../lib/FileManager.h"
#include "Graph.h"

namespace PAA {

class SybilFinder {

private:
	std::set<PAA::Vertex*> honestVertex;
	std::set<PAA::Vertex*> sybilVertex;
	std::set<PAA::Vertex*> seeds;
	PAA::FileManager* fm;
	const static double SEED_PERCENT;
	int seedLength; //Numero de vértices em "seeds"
public:
	SybilFinder();
	void loadSybilFile(std::string&);
	void find(Graph<PAA::Vertex, PAA::Edge>&);
	const std::set<PAA::Vertex*> getHonestVertexSet() const;
	const std::set<PAA::Vertex*> getSybiltVertexSet() const;
	virtual ~SybilFinder();
};

const static double SEED_PERCENT= .2;

} /* namespace PAA */

#endif /* SYBILFINDER_H_ */
