#include "Player.h"
#include "..\..\Game\ConversationManager.h"
#include "..\..\Game\Game.h"

/* cPlayer::cPlayer( unsigned luiX, unsigned luiY, const std::string &lacName, char lcSymbol){
	 
	muiX = luiX; // a little constructor to go a little more faster 
	muiY = luiY;
	macName = lacName;
	mcSymbol = lcSymbol; 
	mbPlayerMove = true; // Already definded in Player.h
} */

void cPlayer::Update(float lfTimestep){


	// Creamos Referencias de los tipos de Acciones( arriba, Abajo, Izq, der)
		const cInputAction & lGoUpAction = cInputManager::Get().GetAction( eIA_GoUp );
		const cInputAction & lGoDownAction = cInputManager::Get().GetAction( eIA_GoDown );
		const cInputAction & lGoRightAction = cInputManager::Get().GetAction( eIA_GoRight );
		const cInputAction & lGoLeftAction = cInputManager::Get().GetAction( eIA_GoLeft );
		const cInputAction & lShootAction = cInputManager::Get().GetAction( eIA_Shoot );
		
		float luiY = this->GetY();  
		float luiX = this->GetX();// Actualizamos posición actual a las coordenadas de Player

	if( !(cConversationManager::Get().IsInConversation()) )// Si NO hay una conversación el jugador PUEDE moverse
		{
			cLevel &lLevel = cGame::Get().GetLevel() ;

		if (lShootAction.GetBecomePressed() )// Si presionamos SPACE
			lLevel.Spawn(luiX, luiY, "PlayerShoot");

		mfDelay += lfTimestep;
		if (mfDelay < kfPLAYER_DELAY)
		return;
		mfDelay = 0.0f;


/*		
		 if ( lGoUpAction.GetIsPressed() ){ // Si el cursor hacia ARRIBA fue pulsado...
					
			luiY--;// posible posición a ocupar por el objeto

				if ( lLevel.IsWall( this->GetX(), luiY) && lLevel.IsInLevel( this->GetX(), luiY) )// y la posición no coincide con un muro
					this->SetY( luiY );// cPlayer Sube !
		}

		 if ( lGoDownAction.GetIsPressed() ){ // Si el cursor hacia ABAJO fue pulsado...
					
			luiY++;// posible posición a ocupar por el objeto

				if ( lLevel.IsWall( this->GetX(), luiY) && lLevel.IsInLevel( this->GetX(), luiY)  )// y la posición no coincide con un muro
					this->SetY( luiY  );// cPlayer Baja !
		}*/

		 if ( lGoRightAction.GetIsPressed() ){ // Si el cursor hacia DERECHA fue pulsado...
					
			luiX++;// posible posición a ocupar por el objeto

				if ( lLevel.IsWall( luiX, this->GetY()) && ( luiX >= 3 && luiX <= 76 ) )// y la posición no coincide con un muro
					this->SetX( luiX );// cPlayer se hace capitalista !
		}

		 if ( lGoLeftAction.GetIsPressed() ){ // Si el cursor hacia IZQUIERDA fue pulsado...
					
			luiX--;// posible posición a ocupar por el objeto

			
				if ( lLevel.IsWall( luiX, this->GetY()) && ( luiX >= 3 && luiX <= 76 ) )// y la posición no coincide con un muro
					this->SetX( luiX );// cPlayer se hace Comunista !
		//		std::stringstream int2Stream;
		//		int2Stream << "\n Moviendo luiX a " << luiX ;
		//		std::string Stream2string = int2Stream.str();
		//		OutputDebugString(Stream2string.c_str());
		}

	}
}

void cPlayer::Render(){
	
	cGraphicManager::Get().SetColor(eLightRed, eBlack);// 
	cGraphicManager::Get().WriteChar( (unsigned) this->GetX(), ( (unsigned) this->GetY()- 1), '\x1e');

	cGraphicManager::Get().WriteChar((unsigned)( this->GetX()- 1), (unsigned)this->GetY(), '\x2f');	
	cGraphicManager::Get().WriteChar((unsigned)this->GetX(), (unsigned)this->GetY(), '\x99');
	cGraphicManager::Get().WriteChar( (unsigned)( this->GetX()+ 1), (unsigned)this->GetY(), '\x5c');

cGraphicManager::Get().SetColor(eRed, eBlack);
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() - 1), (unsigned)(this->GetY()+ 1), '\xdf');
	cGraphicManager::Get().WriteChar((unsigned) this->GetX(), (unsigned)(this->GetY()+ 1), '\xca');//\xca   \xc1  \xcd
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() + 1), (unsigned)(this->GetY()+ 1), '\xdf');
	//cGraphicManager::Get().WriteChar(this->GetX(), this->GetY(), this->GetSymbol());// Few changes !
}