#include "Shoot.h"
#include "..\..\Game\ConversationManager.h"
#include "..\..\Game\Game.h"


void cShoot::Update(float lfTimestep){

				
		// Creamos Referencias de los tipos de Acciones( arriba, Abajo, Izq, der)
		float luiNextY = this->GetY() + mfVY * lfTimestep;  
		float luiNextX = this->GetX() + mfVX * lfTimestep;// Actualizamos posición actual a las coordenadas de Enemy


		if( luiNextY >= 0 && luiNextY <= 24 )
		{
			this->muiY = luiNextY;
		}
		else
		{
			mfVY = -mfVY ;
			this->muiY = this->muiY + mfVY * lfTimestep;
		//	OutputDebugString( " Border AXIS Y TAKEN \n");
		}

		if( luiNextX >= 3 && luiNextX <= 76 )
		{
			this->muiX = luiNextX;
		}
		else
		{
			mfVX = -mfVX ;
			this->muiX = this->muiX + mfVX * lfTimestep;
		//	OutputDebugString( " Border AXIS X TAKEN \n");
		}

}

void cShoot::Render(){
	
	if ( this->macName == "PlayerShoot" )
	cGraphicManager::Get().SetColor(eLightYellow, eBlack);// 
	else
		cGraphicManager::Get().SetColor(eLightGreen, eBlack);

	cGraphicManager::Get().WriteChar( (unsigned)this->GetX(), (unsigned)this->GetY(), this->GetSymbol());// Few changes ! '\xba'

}