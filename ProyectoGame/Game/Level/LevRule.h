#pragma once


//#include "..\Game\Game.h"
#include "Statement.h"
#include <list>


class cLevelRule{
public:
	
	void AddConditionStatement(const cStatement &lStatement ){;}// Necesita implementarse esto
	void AddActionStatement( const cStatement &lStatement ){;}//  y esto

	void EvalRule(){;} // Necesita implementarse esto

private:

	typedef std::list<cStatement> cStatementList;
	typedef  cStatementList::iterator cStatementListIt ;

	cStatementList mConditions;
	cStatementList mActions;

};



