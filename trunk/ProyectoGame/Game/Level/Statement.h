#pragma once

#include <iostream>


enum eStatementType
{
	eStatementContent = 0,
	eStatementRemove,
	eStatementMessage,
	eStatementMove,
	eStatementConversation,
	eStatementExit
};


class cStatement // Sentencias : pueden ser de Condicionales o de Acciónes
{
public:

	eStatementType GetType() {return meType ;}
	std::string GetParam1(){return macParam1 ;}
	std::string GetParam2(){return macParam2 ;}

	void SetType(eStatementType leType) { meType = leType;}
	void SetParam1(std::string lParam1){ macParam1 = lParam1;}
	void SetParam2(std::string lParam2){ macParam2 = lParam2;}
	

	bool Eval(); // Ya implementada en Statement.cpp
 	void Do(); // Implementar esto

private:
	eStatementType meType;
	std::string macParam1;
	std::string macParam2;
};

