#include "LevelRules.h"
#include <list>

void cLevelRules::AddRule(const cLevelRule &lRule)
{
mRuleList.push_back( lRule);
}

void cLevelRules::EvalRules()
{
	for( cLevelRuleListIt lpIterator = mRuleList.begin(); lpIterator != mRuleList.end(); lpIterator++){

		lpIterator->EvalRule(); // EvalRules llamará al EvalRule de cada Regla
	}
}

void cLevelRules::DeInit(){

	for( cLevelRuleListIt lpIterator = mRuleList.begin(); lpIterator != mRuleList.end(); lpIterator++){

		lpIterator->DeInit(); // mientras recorremos la lista de rules llamamos al DeInit de cada Regla
	}
	mRuleList.clear();// limpiamos la lista de reglas
}

void cLevelRule::EvalRule(){

bool lbResult = true;
for(cStatementListIt lpIterator = mConditions.begin(); lpIterator != mConditions.end(); lpIterator++)
{
	lbResult = lbResult && lpIterator->Eval(); 
}

if( lbResult){
	for(cStatementListIt lpIterator = mActions.begin(); lpIterator != mActions.end() ; lpIterator++){
	lpIterator->Do(); // Recorremos y ejecutamos las sentencias de acción..    
	}
}

}

void cLevelRule::AddConditionStatement(const cStatement &lStatement ){
	mConditions.push_back(lStatement);// Agrega un statement a la lista de Condicionales
}

void cLevelRule::AddActionStatement(const cStatement &lStatement ){
	mActions.push_back(lStatement);// Agrega un statement a la lista de acciónes
}


