//	Ejemplo de Bucle de Juego y Gesti�n del Tiempo - Carlos Sebasti�n Lopez -  
//	https://charlysgameproject.googlecode.com/svn/trunk/ - Versi�n Actual: 1.0

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> 

#include "Game\Game.h"

int main(int argc, char *argv[])
{
	lReboot: //Etiqueta Goto , malisima practica, lo s�, cuando aprenda m�s lo mejoro 

	cGame::Get().Init();
	
	unsigned long luiLastTime = timeGetTime(); 

	while (!cGame::Get().HasFinished()) // mientras HasFinished no devuelva el true de finish, continuar� el bucle con Update y render ...
	{
		// Calculando el tiempo en segundos
		unsigned long luiActualTime = timeGetTime(); 

		float lfTimestep = ((float)(luiActualTime - luiLastTime)/ 1000.0f);

		luiLastTime	= luiActualTime;  

		cGame::Get().Update(lfTimestep);
		
		cGame::Get().Render();
	}
		cGame::Get().DeInit();

		if ( cGame::Get().IsPlaying() )
			goto lReboot;
		// a falta del dise�o de un menu y un cambio de estados, vamos a recurr�r a esto para re-comenzar un juego...
	
	return 0;
}
