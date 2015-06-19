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
#include "PAAGraph.h"

namespace PAA {

class SybilFinder {

private:
	std::set<PAA::Vertex*> honestVertex;
	std::set<PAA::Vertex*> sybilVertex;
	std::set<PAA::Vertex*> seeds;

	//Conjunto dos vértice previamente definidos como Sybil
	std::set<std::string> realSybilVertex;

	//Percentual de vértices que serão utilizados como "semente"
	const static double SEED_PERCENT = 0.2;


	PAA::FileManager* fm;
public:
	SybilFinder();
	void loadSybilFile(std::string&);
	void find(PAA::PAAGraph&);
	const std::set<PAA::Vertex*>& getHonestVertexSet() const;
	const std::set<PAA::Vertex*>& getSybiltVertexSet() const;
	const void printRealSybilVertexSet(void) const;
	const void printSeedVertexSet(void) const;
	const void printHonestVertexSet(void) const;
	const void printSybilVertexSet(void) const;
	const void printCandidateVertexSet(std::set<PAA::Vertex*>&) const;
	virtual ~SybilFinder();
private:
	void addRealSybilVertex(std::string&);
	std::set<PAA::Vertex*> chooseSeed(std::set<PAA::Vertex*>&);
	std::set<PAA::Vertex*> getSybilCandidates(std::set<PAA::Vertex*>, std::set<PAA::Vertex*>);
	int getSeedSize(int honestSetSize);
	void addSeeds(PAA::Vertex*);
	void setSeedsSet(std::set<PAA::Vertex*>&);
	Vertex* addToHonestSet(PAA::Vertex*);
	Vertex* addToSybilSet(PAA::Vertex*);
	float calculeCondutanciaNorm(PAA::PAAGraph&);

};



} /* namespace PAA */

#endif /* SYBILFINDER_H_ */
