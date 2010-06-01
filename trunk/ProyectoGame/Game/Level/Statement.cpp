#include "Statement.h"
#include "Level.h"
#include "Object.h"
#include "..\..\Game\Game.h"
#include "..\..\Game\ConversationManager.h"
#include "..\..\Graphics\GraphicManager.h"


bool cStatement::Eval(){// Metodo para consultar Condicionantes ( evaluar dos cosas en un mismo lugar )

	if (meType == eStatementContent){

			cLevel &lLevel = cGame::Get().GetLevel();

			return  (  ( lLevel.IsInCell( macParam1[0], macParam2 ) ) || (lLevel.IsInObject(macParam1, macParam2))  );
			// si param2 está en el mismo lugar de la SpecialCell u Objeto de param1 devolvemos true
	}
	return false;
}

void cStatement::Do(){// Metodo para ejecutar Acciones
	
	switch(meType){
		case 1:{// eStatementRemove

//			std::string lacObject = macParam1 + " Removed \n";
//			OutputDebugString( lacObject.c_str());

			cLevel &lLevel = cGame::Get().GetLevel();			
			lLevel.Remove( macParam1);			
			
			
			;}break;

		case 2:{// eStatementMessage

		//	std::string lacObject = macParam1 + " Message Sended \n";
		//	OutputDebugString( lacObject.c_str());
				
			cGame::Get().PrintMessage(macParam1);// le enviamos una solicitud que imprima el bendito mensaje a Game
			

			;}break;

		case 3:{// eStatementMove

//			std::string lacObject = macParam1 + " moved to " + macParam2 + "\n";
//			OutputDebugString( lacObject.c_str());

			cLevel &lLevel = cGame::Get().GetLevel();
			lLevel.Move( macParam1, macParam2[0]);

			;}break;


		case 4:{// eStatementConversation
			//	std::string lacObject = macParam1 + " moved to " + macParam2 + "\n";
	//		OutputDebugString( "\n Realizando conversación: \n");
			cConversationManager::Get().StartConversation(macParam1); // macParam1 == "Comienzo"

			;}break;

		case 5:{// eStatementExit

			cGame::Get().SetFinish(true);
			;}break;


		default:{// es una Condicional ejecutada como acción
			OutputDebugString(" Error: using Do Method with Conditionants ");
			;}break;
	}

 ;}

