#pragma once
#include "Object.h"
#include <list>
#include "..\..\Graphics\GraphicManager.h"
#include "..\..\Input\InputManager.h"

static const float kfSHOOT_DELAY = 2.5f ;// Esta es la velocidad que se toma en disparar Alien ^_^


class cEnemy : public cObject
{

	float mfDelay;  // Tiempo acumulado para disparar
	float mfVX;		// Velocidad del Enemigo
	float mfVY;

	public:
		cEnemy( unsigned luiX, unsigned luiY, const std::string &lacName, char lcSymbol) : cObject( luiX, luiY, lacName, lcSymbol) 
		{mfVX = 10.0f ; mfVY = 0.0f ; mfDelay = 0.0f;}
		// Heredamos el constructor de cObject

		inline float GetX()							 { return muiX; }
		inline float GetY()						 	 { return muiY; }

		inline void SetX( float luiX )				 { muiX = luiX; }
		inline void SetY( float luiY )				 { muiY = luiY; }

		inline std::string GetName()					 { return macName; }
		inline void SetName( const std::string &lacName ){ macName = lacName;}

		inline void SetSymbol( char lcSymbol )			 { mcSymbol = lcSymbol;}
		inline char GetSymbol()							 { return mcSymbol; }
	
		void Update( float lfTimestep);
		void Render();
		
};