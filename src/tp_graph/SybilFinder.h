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
	const static int NUMBER_OF_SEED = 20;


	PAA::FileManager* fm;
	PAA::FileManager* honestRegionFile;
	PAA::FileManager* sybilRegionFile;
	PAA::FileManager* metricFile;

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
	const void printCandidateVertexSet(std::vector<PAA::Vertex*>&) const;
	void writeHonestVertexSet(const std::string&);
	void writeSybilVertexSet(const std::string&);
	void writeMetrics(const std::string&, PAA::PAAGraph&);
	void resetData(void);
	virtual ~SybilFinder();
	const std::set<std::string>& getRealSybilVertex() const;
	void setRealSybilVertex(const std::set<std::string>& realSybilVertex);

private:
	void addRealSybilVertex(std::string&);
	std::set<PAA::Vertex*> chooseSeed(std::set<PAA::Vertex*>);
	std::vector<PAA::Vertex*> getSybilCandidates(std::set<PAA::Vertex*>, std::set<PAA::Vertex*>);
	int getSeedSize(void);
	void addSeeds(PAA::Vertex*);
	void setSeedsSet(std::set<PAA::Vertex*>&);
	Vertex* addToHonestSet(PAA::Vertex*);
	Vertex* addToSybilSet(PAA::Vertex*);
	float calculeCondutanciaNorm(PAA::PAAGraph&);
	float calculeMedianDegree(PAA::PAAGraph&);
	float calculeModularity(PAA::PAAGraph&);
	float calculeHonestCondutancia(const std::set<PAA::Vertex*>&);
	float calculeSybilCondutancia(const std::set<PAA::Vertex*>&);
	float calculeClusteringCoefficient(const std::set<PAA::Vertex*>&);
	float calculeSybilRightFraction(const std::set<PAA::Vertex*>&, const std::set<std::string>&);
	float calculeHonestRightFraction(const std::set<PAA::Vertex*>&, const std::set<std::string>&);
	float calculeFalsePositive(const std::set<PAA::Vertex*>&,const  std::set<std::string>&);
	float calculeFalseNegative(const std::set<PAA::Vertex*>&, const std::set<std::string>&);
	void openRegionHonestFile(const std::string&);
	void closeRegionHonestFile(void);
	void writeToRegionHonestFile(const std::string&);
	void openRegionSybilFile(const std::string&);
	void closeRegionSybilFile(void);
	void writeToRegionSybilFile(const std::string&);
	void openMetricFile(const std::string&);
	void writeToMetricFile(const std::string&);
	void closeMetricFile(void);
	void openFile(const std::string&,	PAA::FileManager*);
	void closeFile(PAA::FileManager*);
	void writeToFile(const std::string&, PAA::FileManager*);
	void copySetToVector(std::vector<PAA::Vertex*>&, const std::set<PAA::Vertex*>&);

};



} /* namespace PAA */

#endif /* SYBILFINDER_H_ */
