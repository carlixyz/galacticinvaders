
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
	// Initializing mbFinish to false 
	mbFinish = false;

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

void cGame::PrintMessage( std::string &lacMessage){

	mMessage.SetMessage(lacMessage);// Asignamos el mensaje

	mMessage.SetMessageMode( true ); // Level le Asigna true al modo de mensaje de mMessage y este imprime

}

// Function to update the game
void cGame::Update(float lfTimestep)
{
	cInputManager::Get().Update( lfTimestep ); // Actualizando input Manager
				
		// Check the exit condition
		const cInputAction & lAction = cInputManager::Get().GetAction( eIA_CloseApplication );
		if ( lAction.GetIsPressed() ) // si el objeto lAction fué presionado...
		{
			mbFinish = true;  // Se termina !
			return;
		}

	cConversationManager::Get().Update(lfTimestep);// Actualizando Conversation Manager

	mLevel.Update(lfTimestep);// desde allí Llamamos al Update de todos los objetos

	mMessage.Update(lfTimestep);// Actualizamos la duración del Mensaje en pantalla
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
	lGraphic.WriteChars( 52, 24, " GALAXY INVADERS - BETA" );

	// if (mMessage.GetMessageMode())// Si mMessage devuelve true Renderizamos el Mensaje
	mMessage.Render();
	
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


