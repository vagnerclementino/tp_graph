/*
 * SybilFinder.cpp
 *
 *  Created on: 16/06/2015
 *      Author: vagner
 */

#include "SybilFinder.h"
#include <limits>
#include <set>

namespace PAA {

SybilFinder::SybilFinder() {

	std::set<PAA::Vertex*> honestVertex =  std::set<PAA::Vertex*> ();
	std::set<PAA::Vertex*> sybilVertex  =  std::set<PAA::Vertex*> ();
	std::set<PAA::Vertex*> seeds        =  std::set<PAA::Vertex*> ();
	PAA::FileManager* fm				=  new PAA::FileManager();
	int seedLength 						=  std::numeric_limits<int>::min();
}

SybilFinder::~SybilFinder() {

	delete this->fm;

}

void SybilFinder::loadSybilFile(std::string& sybilFileName){

}
void SybilFinder::(Graph<PAA::Vertex, PAA::Edge>& graph){

}
const std::set<PAA::Vertex*> SybilFinder::getHonestVertexSet(void) const{

}
const std::set<PAA::Vertex*> SybilFinder::getSybiltVertexSet(void) const{

}

} /* namespace PAA */
