#include "Player.h"
#include "..\..\Game\ConversationManager.h"
#include "..\..\Game\Game.h"


void cEnemy::Update(float lfTimestep){

				
		// Creamos Referencias de los tipos de Acciones( arriba, Abajo, Izq, der)
		float luiNextY = this->GetY() + mfVY * lfTimestep;  
		float luiNextX = this->GetX() + mfVX * lfTimestep;// Actualizamos posición actual a las coordenadas de Enemy

		if( !(cConversationManager::Get().IsInConversation()) )// Si NO hay una conversación el jugador PUEDE moverse
	{

		if( luiNextY >= 1 && luiNextY <= 20 )
		{
			this->muiY = luiNextY;
		}
		else
		{
			mfVY = -mfVY ;
			this->muiY = this->muiY + mfVY * lfTimestep;
		//	OutputDebugString( " Border AXIS Y TAKEN \n");
		}

		if( luiNextX >= 3 && luiNextX <= 76)
		{
			this->muiX = luiNextX;
		}
		else
		{
			mfVX = -mfVX ;
			this->muiX = this->muiX + mfVX  * lfTimestep ;
		//	OutputDebugString( " Border AXIS X TAKEN \n");
		}
		
		if (this->GetSymbol() == 'S'){
		mfDelay += lfTimestep;
		if (mfDelay < kfSHOOT_DELAY)
		return;
		mfDelay = 0.0f;
		
			cLevel &lLevel = cGame::Get().GetLevel() ;
			lLevel.Spawn(this->muiX, this->muiY, "AlienShoot");
		}

	}

}

void cEnemy::Render(){
	
	if(this->GetSymbol() == 'B')// Renderizamos un Bicho cualquiera
	{
	cGraphicManager::Get().SetColor(eLightGreen, eBlack);// 
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2), (unsigned)(this->GetY()- 1), '\xbf');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)(this->GetY()- 1), '\x5c');
	cGraphicManager::Get().WriteChar( (unsigned)this->GetX(), (unsigned)(this->GetY()- 1), '\x1f');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1), (unsigned)(this->GetY()- 1), '/');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2), (unsigned)(this->GetY()- 1), '\xda');

	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2), (unsigned)this->GetY(), '\xc0');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)this->GetY(), '\x1f');
	cGraphicManager::Get().WriteChar((unsigned) this->GetX(),(unsigned) this->GetY(), ' ');//  Hit Here to kill !
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1),(unsigned) this->GetY(), '\x1f');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2),(unsigned) this->GetY(), '\xd9');
 
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2),(unsigned) (this->GetY()+ 1), '/');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)(this->GetY()+ 1), '\xee');
	cGraphicManager::Get().WriteChar((unsigned) this->GetX(), (unsigned)(this->GetY()+ 1), '\xdf');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1),(unsigned) (this->GetY()+ 1), '\xee');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2),(unsigned) (this->GetY()+ 1), '\x5c' );
	}
	else if( this->GetSymbol() == 'S')// Renderizamos un "Escupidor"
	{
	cGraphicManager::Get().SetColor(eYellow, eBlack);// 
//	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -3), (unsigned)(this->GetY()- 1), '\xda');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2), (unsigned)(this->GetY()- 1), '\xda');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)(this->GetY()- 1), '\x4');
	cGraphicManager::Get().WriteChar( (unsigned)this->GetX(), (unsigned)(this->GetY()- 1), '\xc2');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1), (unsigned)(this->GetY()- 1), '\x4');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2), (unsigned)(this->GetY()- 1), '\xbf');
//	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +3), (unsigned)(this->GetY()- 1), '\xbf');

	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -3), (unsigned)this->GetY(), '\xda');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2), (unsigned)this->GetY(), '\xc5');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)this->GetY(), '\x4');
	cGraphicManager::Get().WriteChar((unsigned) this->GetX(),(unsigned) this->GetY(), '\xc5');// Hit Here to kill !
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1),(unsigned) this->GetY(), '\x4');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2),(unsigned) this->GetY(), '\xc5');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +3),(unsigned) this->GetY(), '\xbf');
 
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -3),(unsigned) (this->GetY()+ 1), '\xd9');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2),(unsigned) (this->GetY()+ 1), '\xc0');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)(this->GetY()+ 1), '\x7b');
	cGraphicManager::Get().WriteChar((unsigned) this->GetX(), (unsigned)(this->GetY()+ 1), '\xdd');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1),(unsigned) (this->GetY()+ 1), '\x7d');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2),(unsigned) (this->GetY()+ 1), '\xd9' );
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +3),(unsigned) (this->GetY()+ 1), '\xc0' );
	}
	else if ( this->GetSymbol() == 'G')// Renderizamos un Fantasma 
		{
	cGraphicManager::Get().SetColor(eGreen, eBlack);// 

	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2), (unsigned)(this->GetY()- 1), '\xda');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)(this->GetY()- 1), '\x10');
	cGraphicManager::Get().WriteChar( (unsigned)this->GetX(), (unsigned)(this->GetY()- 1), '\xc1');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1), (unsigned)(this->GetY()- 1), '\x11');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2), (unsigned)(this->GetY()- 1), '\xbf');

	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -3), (unsigned)this->GetY(), '\xda');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2), (unsigned)this->GetY(), '\xc1');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)this->GetY(), '\xc5');
	cGraphicManager::Get().WriteChar((unsigned) this->GetX(),(unsigned) this->GetY(), '\xc5');//  Hit Here to kill !
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1),(unsigned) this->GetY(), '\xc5');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2),(unsigned) this->GetY(), '\xc1');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +3),(unsigned) this->GetY(), '\xbf');
 
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -3),(unsigned) (this->GetY()+ 1), '\xc0');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -2),(unsigned) (this->GetY()+ 1), ' ');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() -1), (unsigned)(this->GetY()+ 1), '\xc0');
	cGraphicManager::Get().WriteChar((unsigned) this->GetX(), (unsigned)(this->GetY()+ 1), ' ');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +1),(unsigned) (this->GetY()+ 1), '\xd9');
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +2),(unsigned) (this->GetY()+ 1), ' ' );
	cGraphicManager::Get().WriteChar( (unsigned)(this->GetX() +3),(unsigned) (this->GetY()+ 1), '\xd9' );

	}

}