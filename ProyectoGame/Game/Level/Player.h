
#pragma once
#include "Object.h"
#include <list>
#include "..\..\Graphics\GraphicManager.h"
#include "..\..\Input\InputManager.h"

static const float kfPLAYER_DELAY = 0.025f ;// Inserte aqui su velocidad deseada para el modo Release ^_^


class cPlayer : public cObject
{
	public:
		cPlayer( unsigned luiX, unsigned luiY, const std::string &lacName, char lcSymbol) : cObject( luiX, luiY, lacName, lcSymbol)
		{mfDelay = 0.0f;  }

		float mfDelay;
		
		// Heredamos el constructor de cObject kfDELAY = 5.0f;

		inline float GetX()							 { return muiX; }
		inline float GetY()						 	 { return muiY; }

		inline void SetX( float luiX )				 { muiX =  luiX; }
		inline void SetY( float luiY )				 { muiY =  luiY; }

		inline std::string GetName()					 { return macName; }
		inline void SetName( const std::string &lacName ){ macName = lacName;}

		inline void SetSymbol( char lcSymbol )			 { mcSymbol = lcSymbol;}
		inline char GetSymbol()							 { return mcSymbol; }

		void Update( float lfTimestep);
		void Render();
		
};