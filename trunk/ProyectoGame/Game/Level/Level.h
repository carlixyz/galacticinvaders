#pragma once

#include <tinystr.h>
#include <tinyxml.h>
#include <Windows.h> 
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Shoot.h"

#include "Statement.h"
#include "LevelRules.h"



class cLevel
{
 	unsigned int muiWidth; // Estas podrían variar de un nivel al otro ?
 	unsigned int muiHeight; //  en todo caso no serían constantes... :Z
	unsigned int muiArea;

	bool * mabMap ; // Creamos un array dinamico unidimensional que inicializará en Init
	
	// Uso de typedef para simplificar la sintax
	typedef std::list<cSpecialCell> cSpecialCellDictionary ;
	typedef cSpecialCellDictionary::iterator cSpecialCellDictionaryIt ;
	
	typedef std::list<cObject *> cObjectList;
	typedef cObjectList::iterator cObjectListIt;

	// List Declaration
	cSpecialCellDictionary mDictionary;
	
	// List of Objects Declaration
	cObjectList mObjects;

	cLevelRules mLevelRules;// Reglas contenidas en el Level

	public:
			
		bool Init(const char * lacLevelFile); // function to initialize the game

		void Update(float lfTimestep); // Function to update the Level

		void Render(); // función para renderizar el level

		bool DeInit(); //Función para DesInicializar the level

		bool IsInLevel(float luiX,float luiY) { return(( (float) muiWidth <= (luiY * (float) muiWidth + luiX)) && ((luiY * (float) muiWidth + luiX) <= (float) muiArea)) ;}

		bool IsWall(float luiX,float luiY)  { return mabMap[((unsigned)luiY * muiWidth) +(unsigned) luiX];}// Retorna 1 (true) si no hay muros

		bool IsInCell(char lacParam1, std::string lacParam2);

		bool IsInObject(std::string lacName1, std::string lacName2);

		void Spawn(float luiX,float luiY, std::string lacName );

		void Remove( std::string lacName );

		void Move( std::string lacName, char lcCellPosition );

		
	protected:
	//cLevel(void){;} // Constructor protegido
	
};

