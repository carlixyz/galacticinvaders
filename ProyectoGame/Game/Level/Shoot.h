
#pragma once
#include "Object.h"
#include <list>
#include "..\..\Graphics\GraphicManager.h"
#include "..\..\Input\InputManager.h"

class cShoot : public cObject
{

	float mfVX;		// Velocidad del Disparo
	float mfVY;

	public:
		cShoot( unsigned luiX, unsigned luiY, const std::string &lacName,float mfSpeed , char lcSymbol) : cObject( luiX, luiY, lacName, lcSymbol)
		{mfVX = 0.0f; mfVY = mfSpeed ;}
		// Heredamos el constructor de cObject

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