/*
 * Vertex.h
 *
 *  Created on: 14/06/2015
 *      Author: Vagner Clementino
 */

#ifndef VERTEX_H_
#define VERTEX_H_
#include <set>
#include <string>
#include "Edge.h"



namespace PAA {

class Edge;

enum Color{
		WHITE = 0,
		GREY = 1,
		BLACK = 2
	};



class Vertex {

private:
	std::string name;    		  // Nome ou label do vértice
	std::set<PAA::Edge*> arcs;    // Lista de aresta que deixam o vértice
	std::set<PAA::Edge*>& edges;  // Definindo um alias para o arcs
	double cost;        		  // Custo para alcançar este vértices, valor padrão igual a 0 (zero)
	bool visited;       		 // Define se o vértice já foi visitado; valor padrão igual false
	PAA::Color color;			// Define a cor de vértice; valor padrão BRANCO
	Vertex* previous;   		// Vértice que vem antes deste, valor padrão igual a NULL
	bool isSybil;			    // Define se o um vértice é Sybil - Default TRUE

public:
	Vertex(const std::string& name = "");
	//Construtor para construçaõ de uma cópia
	Vertex(const Vertex& other);
	virtual ~Vertex();

	//Métodos para acesso e alteração do atributo 'Name'
	const std::string& getName(void)const;
	void setName(const std::string&);

	//Métodos para acesso e alteração do atributo 'Cost'
	double getCost(void)const;
	void setCost(double);

	//Métodos para acesso e alteração do atributo 'Visited'
	bool getVisited(void)const;
	void setVisited(bool);

	//Métodos para acesso e alteração do atributo 'Color'
	PAA::Color getColor(void) const;
	void setColor(PAA::Color newColor);

	//Métodos para acesso e alteração do atributo 'Edges'
	std::set<Edge*>& getEdges(void) const;
	void setEdges(std::set<Edge*>&);

	//Métodos para acesso e alteração do atributo 'previous'
	Vertex* getPreviousVertex(void) const;
	void setPreviousVertex(Vertex*);

	//Métodos para acesso e alteração do atributo 'isSybil'
	bool getIsSybil(void) const;
	void setIsSybil(bool);

	//Retorna os valores dos atributos para seu valor padrão
	void resetData(void);

	//Retorna uma string represetando o vértice
	std::string toString() const;

	//Atributo de cópia de veŕtice para outro
	Vertex& operator =(const Vertex& other);

	//Adiciona um um aresta para um vértice
	PAA::Edge* addEdges(PAA::Edge*);

	//Remove uma aresta de vértice
	PAA::Edge* removeEdge(PAA::Edge*);

};

	//Método para permitir que o vértice seja impresso em stream de saída
	std::ostream& operator<<(std::ostream& out, const Vertex& v);

} /* namespace PAA */

#endif /* VERTEX_H_ */
