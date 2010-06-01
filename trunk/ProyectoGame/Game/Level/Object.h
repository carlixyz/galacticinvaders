#pragma once

#include <list>
#include "..\..\Graphics\GraphicManager.h"

enum eSpecialCellContent
{
eObject = 0,
ePlayer,
eSpecialLocation,
eEnemy
};// Aqui es donde hay que modificar primero si deseamos agregar un objeto diferente

struct cSpecialCell
{
	inline cSpecialCell(char & Id, unsigned & x, unsigned & y) {mcId = Id; miX = x; miY = y; }

	char mcId; //Cell Id en el Xml 
	int miX; // Ubicación en el Level
	int miY;

	char mcSymbol; // Simbolo Renderizado en el Nivel

	eSpecialCellContent meCellContent; //Enum del Tipo de Contenido de celda
	std::string mName; // Nombre propio
};

class cObject // Clase Objeto generica
{
	public:
		cObject(unsigned luiX, unsigned luiY, const std::string &lacName, char lcSymbol) 
		{ muiX = (float) luiX; muiY = (float) luiY; macName = lacName; mcSymbol = lcSymbol;}
		// a little constructor to go faster

		inline float GetX()						 { return muiX; }
		inline float GetY()						 { return muiY; }
		inline void SetX( unsigned luiX )				 { muiX = (float) luiX; }
		inline void SetY( unsigned luiY )				 { muiY = (float) luiY; }

		inline std::string GetName()					 { return macName; }
		inline void SetName( const std::string &lacName ){ macName = lacName;}

		inline void SetSymbol( char lcSymbol )			 { mcSymbol = lcSymbol;}
		inline char GetSymbol()							 { return mcSymbol; }



		virtual void Update( float lfTimestep)			 { ;}
		virtual void Render()
		{
			cGraphicManager::Get().SetColor( eLightWhite, eBlack);// Create a Object.cpp just for this ? nah...
			cGraphicManager::Get().WriteChar((unsigned) muiX,(unsigned) muiY, mcSymbol);
		}

protected:
		std::string macName;// nombre
		float muiX;		// Posición
		float muiY;
		char mcSymbol;		//Symbolo a Renderizar

};

struct cCollision // estructura para capturar objetos que collisionan entre si...
{
cObject * lpObject1;
cSpecialCell * lpSpecialCell;
};


