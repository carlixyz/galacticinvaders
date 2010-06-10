
#pragma once


#include "..\Utility\singleton.h"// singleton est� en la carpeta utility
#include <tinystr.h>
#include <tinyxml.h>
#include "..\Game\Level\Level.h"
#include "..\Game\Level\Message.h"


class cGame : public cSingleton<cGame>
{
	friend class cSingleton<cGame>;

	bool mbFinish;// presionando escape se sale del program

	bool mbPlaying; // Maquina de estados, sep, algo por el estilo

	cLevel mLevel;

	cMessage mMessage;

	int miLives ;

	int miScore ;	// General data Stats

	protected:
		cGame(){ ; } // protected Constructor 

	public:
	
		bool Init(); // function to initialize the game

		void Update(float lfTimestep); // Function to update the game

		void Render(); // funci�n para renderizar el juego

		bool DeInit(); //Funci�n para DesInicializar the game

		cLevel &GetLevel() {return mLevel ;}

		// funci�n "ha Finalizado" de cierre del loop 
		inline bool HasFinished()	{ return mbFinish; }

		// funci�n rapida para determinar estado del juego
		inline bool IsPlaying() { return mbPlaying;  }

		//Funciones para actualizar status de cantidad de vidas y puntos del jugador
		inline void PlayerDies() { miLives = miLives - 1; }

		inline void PlayerScored(int liPoints) { miScore += liPoints ;  }

		// funci�n para determinar si el jugador est� jugando o no
		inline void SetPlayingMode(bool lbMode) { mbPlaying = lbMode ; }

		void SetFinish(bool lbSwitch) { mbFinish = lbSwitch;  }

		void PrintMessage( std::string &lacMessage);
		
};


