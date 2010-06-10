
#include <stdio.h>
#include <stdlib.h>
#include "..\Game\Game.h"
#include "..\Game\Level\Level.h"
#include "..\Input\InputManager.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Game\ConversationManager.h"


extern tActionMapping kaActionMapping[];


// function to initialize the game
bool cGame::Init()
{	
	// Initializing a lot of Vars 
	mbFinish = false;

	mbPlaying = true;

	miLives = 3;

	miScore = 0 ;
	

	// Inicialización de la clase InputManager ( y tooodas las cosas que esta hace... )
	cInputManager::Get().Init(kaActionMapping, eIA_Count);

	mLevel.Init(".\\Data\\Level.xml");

	// Inicializando GraphicManager
	cGraphicManager::Get().Init();

	cConversationManager::Get().Init(".\\Data\\Conversation.xml"); // It´s suposse to Init and read ConversationManager
	cConversationManager::Get().StartConversation("Comienzo"); // Activar este para realizar una comica charla al iniciar el juego

	mMessage.Init();// Inicializamos los atributos del mensaje
	
	return true;
}

void cGame::PrintMessage( std::string &lacMessage)
{
	if ( ( lacMessage != "GAME OVER" ) || ( miLives == 0 ) )
	{
	mMessage.SetMessage(lacMessage);// Asignamos el mensaje

	mMessage.SetMessageMode( true ); // Level le Asigna true al modo de mensaje de mMessage y este imprime
	}
}

// Function to update the game
void cGame::Update(float lfTimestep)
{
	cInputManager::Get().Update( lfTimestep ); // Actualizando input Manager
				
		// Check the exit condition
		const cInputAction & lAction = cInputManager::Get().GetAction( eIA_CloseApplication );
		const cInputAction & lStart = cInputManager::Get().GetAction( eIA_Shoot );		

		if ( lAction.GetIsPressed() ) // si el objeto lAction fué presionado...
		{
			mbPlaying = false; // no se juega más y
			mbFinish = true;  // Se termina !
			return;
		}

	cConversationManager::Get().Update(lfTimestep);// Actualizando Conversation Manager

	mLevel.Update(lfTimestep);// desde allí Llamamos al Update de todos los objetos

	mMessage.Update(lfTimestep);// Actualizamos la duración del Mensaje en pantalla


		if ( !this->IsPlaying() && !this->HasFinished() && lStart.GetIsPressed() ) // Si se presionó Shoot y no se está jugando ni terminó 
	{
		if ( miLives ) // Si el jugador tiene Vidas aún...
		{
				mLevel.Spawn( 40, 21, "Player"); 
				mbPlaying = true ; // Juega con una nueva nave
		}
		else // Sino el juego ha terminado y debe reecomenzar
		{
				mbPlaying = true ; 
				mbFinish = true;
		}
	}
}


// función para renderizar el juego
void cGame::Render()
{
	// Get the graphic manager
	cGraphicManager & lGraphic = cGraphicManager::Get();
		// Clear the buffers
	lGraphic.SetColor(eWhite, eBlack);
	lGraphic.ClearBuffer();

	mLevel.Render(); // Llamamos al Render del nivel

	cConversationManager::Get().Render();

	lGraphic.SetColor( eLightPurple, eBlack); 
	lGraphic.WriteChars( 2, 24, " LIVES = " );// Rendering Lives Left
	std::stringstream lsLives;
	lsLives << miLives ;
	lGraphic.WriteChars( 12, 24, lsLives.str().c_str() );
	
	lGraphic.WriteChars( 62, 24, " SCORE " );  // Rendering total Score
	std::stringstream lsScore;
	lsScore << miScore ;
	lGraphic.WriteChars( 70, 24, lsScore.str().c_str() );

	lGraphic.SetColor( eWhite, eBlack);
	lGraphic.WriteChars( 28, 24, " -< HIGH SCORE 20000 >- " ); // Rendering Fake Score

	// if (mMessage.GetMessageMode())// Si mMessage devuelve true Renderizamos el Mensaje
	mMessage.Render();

	if ( !this->IsPlaying() && !this->HasFinished() )
	{
		if ( miLives )
			lGraphic.WriteChars( 8, 22, " Your SpaceShip Was Destroyed - Press Space Bar to Try Again " );
		else
		{
			lGraphic.WriteChars( 8, 22, " The Human Race is DoOMed! - Press Space Bar to Start a New Game " );
		}
	}
	
	//Swap the buffers
	lGraphic.SwapBuffer();
}

//Función para DesInicializar the game
bool cGame::DeInit()
{
	cInputManager::Get().Deinit();  // Deinicializando input Manager

	cGraphicManager::Get().Deinit();// idem graphic manager

	mLevel.DeInit();

	cConversationManager::Get().DeInit();
	
	return true;
}


