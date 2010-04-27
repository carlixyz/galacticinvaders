#pragma once

//#include "Level.h"
#include <Windows.h> 
#include "Statement.h"
#include <list>

class cLevelRule // Regla Con lista de Condiciones y lista de acciones
{
public:
	void AddConditionStatement(const cStatement &lStatement );// It´s done
	void AddActionStatement( const cStatement &lStatement );//  and this too

	void EvalRule(); // esto está implementado para multiples condiciones
	void DeInit(){mConditions.clear(); mActions.clear();}// limpiamos las conds y actions de cada Regla

private:

	typedef std::list<cStatement> cStatementList;
	typedef  cStatementList::iterator cStatementListIt ;

	cStatementList mConditions;
	cStatementList mActions;
};



class cLevelRules // Lista de Reglas
{
public:
	
	void AddRule( const cLevelRule &lRule);//Esto está implementado en LevelRules.cpp
	void EvalRules();// Esto también ya está
	void DeInit();// DeInicializamos

private:
	typedef std::list<cLevelRule> cLevelRuleList;
	typedef cLevelRuleList::iterator cLevelRuleListIt;

	cLevelRuleList mRuleList;

};


