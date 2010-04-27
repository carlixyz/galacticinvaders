
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

	cLevel mLevel;

	cMessage mMessage;

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

		void SetFinish(bool lbSwitch) { mbFinish = lbSwitch;  }

		void PrintMessage( std::string &lacMessage);
		
};


