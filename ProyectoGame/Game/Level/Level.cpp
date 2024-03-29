#include "Level.h"
#include <assert.h>
#include "..\..\Input\InputManager.h"
#include "..\..\Game\ConversationManager.h"


bool cLevel::Init(const char * lacLevelFile)
{
	
	TiXmlDocument doc(lacLevelFile);
	bool lbLoadOk = doc.LoadFile();
	if ( lbLoadOk )
	{	
		TiXmlHandle docHandle( &doc ); // Buscamos el Handle del Documento
		TiXmlElement *pElem; 
		TiXmlAttribute* pAttrib; // Con estos punteros controlamos Elementos y Atributos
		
		// Buscamos el primer elemento "Level" y tomamos el primer attributo de este
		pAttrib= docHandle.FirstChildElement().Element()->FirstAttribute(); 
		
		//Inicializamos las dimensiones del map
		muiWidth = atoi(pAttrib->Value()); //con atoi asignamos const char * a int
		muiHeight = atoi(pAttrib->Next()->Value());
		muiArea = muiWidth * muiHeight; //Area : 1600 =  20 * 80

		mabMap = new bool [muiArea];// Iniciamos el array con el Tamaño de Area 
		
				
		// Ahora vamos a cargar el mapa en el Array buscando en / Doc / Level / Map / < Row >
		pElem = docHandle.FirstChildElement().FirstChildElement().FirstChildElement().ToElement(); 
		std::string lsLine ;
		

		// CARGANDO LA ESTRUCTURA DEL MAPA
				
			for( unsigned luiY = 0 ; pElem; pElem=pElem->NextSiblingElement() ){//Si hay Rows en el xml los leemos
						
				std::string lsLine = pElem->GetText(); // Cargamos el Texto de cada uno de los rows por linea en un string
			 			 
				for ( unsigned luiX = 0 ; luiX != lsLine.size(); luiX++){// Recorremos los caracteres del string (luiX)
				// recorremos el array unidimensional mabMap con el mismo mecanismo de Backbuffer y asignamos true o false

					// la 1º linea asigna true si es != de '#' 
						mabMap[luiY * muiWidth + luiX] = (lsLine[luiX] != '#');//más Legible usar // unsigned luiIndex = luiY * muiWidth + luiX;
					// y en la 2º si es true pero es != de ' ' (espacio), entonces tenemos un SpecialCell  	
						if ( mabMap[luiY * muiWidth + luiX] && lsLine[luiX] != ' ' )
						{
						cSpecialCell lSpCell(lsLine[luiX], luiX, luiY );		
						mDictionary.push_back(lSpCell);	// Inicializamos la estructura y la guardamos en la lista
						}					
				} 
				if (luiY <= muiHeight)
				luiY++;// Recorremos el alto (luiY) del array hasta que esté completo...
			}
		//END OF LOOP OF THE DEAD!! ! !

		// CARGANDO LA INFORMACIÓN DE LAS SPECIAL CELLS
		// En el XML Accedemos a / Doc / Level / SpecialCells /< Cell > 
		pElem = docHandle.FirstChildElement().FirstChildElement("SpecialCells").FirstChildElement().ToElement(); 
	
		// Iniciamos y Recorremos nuestro diccionario de Celdas especiales... IN DA LOOP OF DA DEAD 2.0 ! ! !
		for (cSpecialCellDictionaryIt lpIterator = mDictionary.begin(); lpIterator !=  mDictionary.end() ; lpIterator++ ){
						
			// y recorremos las celdas Hijas de SpecialCells en el Xml...
			for(TiXmlElement *pCell = pElem ; pCell ; pCell=pCell->NextSiblingElement() ) {
			
				// comparamos el valor que apunta el Iterador a la estructura con el que apunta (*pElem) al 1º atributo en el Xml 
				if ( lpIterator->mcId == *pCell->FirstAttribute()->Value() ){ // Si encontramos coincidencias con el Id de nuestra SpecialCell...
					
					pAttrib = pCell->FirstAttribute()->Next(); // Asignamos el resto de los atributos que corresponden:
					const char *pacContent = pAttrib->Value();// 

					//1 Designamos el TIPO DE CONTENIDO en el enum de los SpecialCells  
					if (!strcmp(pacContent, "Special Location"))
						lpIterator->meCellContent = eSpecialLocation;	

					else // Si no tenemos Special Location (caso más común) buscamos al player y sino se trata de un objeto ( y sino estamos leyendo otro .Xml ) 
						if(!strcmp(pacContent, "Player"))
							lpIterator->meCellContent = ePlayer;
						else if (!strcmp(pacContent, "Object"))
						lpIterator->meCellContent = eObject;
						else if (!strcmp(pacContent, "Enemy"))
						lpIterator->meCellContent = eEnemy;
					//Si deseamos agregar un tipo de objeto diferente cambiar el ultimo por operador ternario por un else if

					if( pAttrib)
						pAttrib = pAttrib->Next();//otro Operador Ternario: Si hay atributos, Asignamos el NOMBRE a SpecialCell sino null													
					(pAttrib)? lpIterator->mName = pAttrib->ValueStr() :  lpIterator->mName = "NULL" ;  
					
					// Si hay más atributos, Asignamos el CARACTER de Renderizado Sino igual hay que asignar algo podrían surgir errores!
					(pAttrib) ? lpIterator->mcSymbol = *(pAttrib->Next()->Value()) : lpIterator->mcSymbol = ' ' ;
				}
			}
		}

		// CREANDO LOS OBJETOS
			for (cSpecialCellDictionaryIt lpIterator = mDictionary.begin(); lpIterator !=  mDictionary.end() ; lpIterator++ ){
		 	switch(lpIterator->meCellContent){
				case 0:
					{// Enum 0; si Tenemos una casilla del tipo eObject lo inicializamos y agregamos a la lista mObjects
			//		miGlobalIndex = miGlobalIndex++ ;
					cObject * lpObject = new cObject(lpIterator->miX, lpIterator->miY, lpIterator->mName, lpIterator->mcSymbol);
					mObjects.push_back(lpObject);
					}
					break;
			
				case 1:
					{// Enum 1;  Tenemos al Player, un variedad de objeto, hay que inicializarlo e incluirlo en mObjects
			//		miGlobalIndex = miGlobalIndex++ ;
					cObject * lpObject = new cPlayer(lpIterator->miX, lpIterator->miY, lpIterator->mName,lpIterator->mcSymbol);
					mObjects.push_back(lpObject);
				
					}
					break;

				case 3:
					{// Enum 3;  Tenemos al enemigo, una variedad de objeto, hay que inicializarlo e incluirlo en mObjects
					//cada enemigo que creamos le registramos un numero de identificación
					cObject * lpObject = new cEnemy(lpIterator->miX, lpIterator->miY, lpIterator->mName, lpIterator->mcSymbol);
					mObjects.push_back(lpObject);
					}
					break;


				default:{// Enum 2; una eSpecialLocation (no hacemos nada)
					//{cObject * lpObject = new cObject(lpIterator->miX, lpIterator->miY, lpIterator->mName,*lpIterator->mcSymbol);
					//	mObjects.push_back(lpObject);
					;}
					break;
			}
		}
		
			// CARGANDO LAS REGLAS
		// Accedemos y mostramos a / Doc / Level / Rules /( Usando Indices, en este caso el 3er elemento de Level, Rules)
		pElem = docHandle.FirstChildElement().ChildElement(2).ToElement(); 
		assert( pElem->ValueStr() == "Rules" );//verificar si hay < Rules >		
			
		// Doc / Level / Rules (pElem) / If		
		for ( pElem = pElem->FirstChildElement() ;pElem ; pElem = pElem->NextSiblingElement()){  //Vamos a recorrer los "If" de Rules que son las REGLAS 
		
			cLevelRule lLevelRule; //Por cada If Declaramos una nueva Regla  
			
			// Ingresamos en los Ifs: y vemos sus condicionales y sus acciónes " 
			for (TiXmlNode* pChild = pElem->FirstChildElement()->ToElement(); pChild; pChild = pChild->NextSiblingElement()){//CONDICIONALES Y ACCIONES
								
				// Mostramos dentro de los conds y Thens los contenidos... entra a la cancha pSubChild ... XD //CONTENT, MOVE, MESSAGE, REMOVE, EXIT
				for (TiXmlElement * pSubChild = pChild->FirstChildElement()->ToElement(); pSubChild; pSubChild = pSubChild->NextSiblingElement() ){

					cStatement lStatement;//por cada subhijo Declaramos un nuevo statement que vamos a definir a continuación

					//Definimos el Tipo de Contenido del Statement:
					if(pSubChild->ValueStr() == "Content") // Contenido 0 (Condicional, caso + común)
						lStatement.SetType(eStatementContent);
					else{				
					if(pSubChild->ValueStr() == "Message")// Acción 2
						lStatement.SetType(eStatementMessage);
										
					if(pSubChild->ValueStr() == "Remove")// Acción 1
						lStatement.SetType(eStatementRemove);
				
					if(pSubChild->ValueStr() == "Move")// Acción 3
						lStatement.SetType(eStatementMove);
					
					if(pSubChild->ValueStr() == "Conversation")// Acción 4
						lStatement.SetType(eStatementConversation);

					if(pSubChild->ValueStr() == "Exit")// Acción 5
						lStatement.SetType(eStatementExit);

					if(pSubChild->ValueStr() == "UpdateStats")// Acción 6
						lStatement.SetType(eStatementUpdateStats);
					}
				
					pAttrib = pSubChild->FirstAttribute();// Comenzamos a indagar los attributos para definir los Param1 y Param2 de lStatement
					
				if (  pAttrib ){//si existe, Asignando Parametro 1 a lStatement					
						lStatement.SetParam1(pAttrib->ValueStr()); // Estos parametros tienden a ser un caracter por ello todos irán a Param1
						pAttrib= pAttrib->Next(); //Recorriendo siguiente Attributo...

						if (  pAttrib )// Asignando Parametro 2 a lStatement, si existe también, y sino terminamos por que no son mayores de pares los atributos
						lStatement.SetParam2(pAttrib->ValueStr()); 
					}
				
					if(pChild->ValueStr() == "Conds")//Si el Statement es uno de tipo Condicional lo Guardamos en ConditionStatement de la Regla (LevelRule)
					lLevelRule.AddConditionStatement(lStatement);
					else 
						if(pChild->ValueStr() == "Then")//Si el Statement es uno de tipo Acción lo Guardamos en ActionStatement de la Regla (LevelRule)
					lLevelRule.AddActionStatement(lStatement);
				
				}// Ufff que largo, espero que esto esté bien...
			}
			mLevelRules.AddRule(lLevelRule);// al final guardamos la regla con sus listas de  actions y conditions statements, en mLevelRules..
		}
				
		OutputDebugString("\n XML Load: OK\n");
		}
	else
	{
		OutputDebugString("XML Load: FAILED\n");
	}
	return true;
}

bool cLevel::IsInCell(char lacParam1, std::string lacParam2)
{// Esta Función evalua que el Objeto del segundo parametro esté en el lugar del caracter Special cell
	// Recorremos la lista de colisiones buscando la Cell y el objeto  

	for (cCollisionIt lpIterator = mCollisions.begin(); lpIterator !=  mCollisions.end() ; ++lpIterator )
	{
		if ( ( lpIterator->lpSpecialCell->mcId == lacParam1 ) && ( lpIterator->lpObject1->GetName() == lacParam2 ) )
		{// Si encontramos una colision cuyos dos objetos coinciden en el tipo o Id ..

	/*		cCollision lResults; 
			lResults.lpObject1 = lpIterator->lpObject1;
			lResults.lpSpecialCell = lpIterator->lpSpecialCell;
			mRemoveList.push_back(lResults); // los incluimos en una lista de Borrado ( aunque no vamos a borrar al Special Cell )
		 	OutputDebugString("Collision Detected \n");*/

			return true; // y luego devolvemos true
		}
	}
	return false;
}


bool cLevel::IsInObject(std::string lacName1, std::string lacName2){
// Esta Función evalua que el Objeto del segundo parametro esté en el lugar del Objeto del primer Parametro

		// Recorremos la Lista de objetos para el primer objeto...
	for (cObjectListIt lpIterator1 = mObjects.begin(); lpIterator1 !=  mObjects.end() ; lpIterator1++ )
	{
		// Recorremos la Lista de objetos para el segundo objeto...
		for (cObjectListIt lpIterator2 = mObjects.begin(); lpIterator2 !=  mObjects.end() ; lpIterator2++ )
		{ 
			
			// si encontramos un Objeto con el nombre de lacName2 y otro con el nombre de lacName1...
			if((*lpIterator2)->GetName() == lacName2 && (*lpIterator1)->GetName() == lacName1 )
			{
				
				// y si la posición de este objeto (lacName2) coincide con la del otro objeto (lacName1)
				if( ((unsigned)(*lpIterator2)->GetX() == (unsigned)(*lpIterator1)->GetX() ) && 
					( (unsigned)(*lpIterator2)->GetY() == (unsigned)(*lpIterator1)->GetY()) )
				{
					// Aqui habría que identificar los objetos individualmente
					 return true; //Devolvemos el resultado de la condicional (true)
				}
			}//sino seguimos buscando más objetos con esas características
		}	
	}

	return false;
}


void cLevel::Move(std::string lacName, char lcCellPosition ){

	// Recorremos la Lista de objetos...
	for (cObjectListIt lpIterator = mObjects.begin(); lpIterator !=  mObjects.end() ; lpIterator++ ){ 

		//y por cada uno Recorremos la lista de Celdas Especiales...
		for (cSpecialCellDictionaryIt lpCellIterator = mDictionary.begin(); lpCellIterator != mDictionary.end(); lpCellIterator++){
	
			// si tenemos un Objeto con el nombre de lacName y una Celda con el Id caracter  lcCellPosition...
			if((*lpIterator)->GetName() == lacName && lpCellIterator->mcId == lcCellPosition ){
				
				// cambiamos la posición de este objeto (lacName) por la de la Speciall Cell (lcCellPosition)
				 (*lpIterator)->SetX(lpCellIterator->miX) ;
				 (*lpIterator)->SetY(lpCellIterator->miY) ;
			}
		}
	}	
}

void cLevel::Remove( std::string lacName ){

	// Recorremos la Lista de objetos...
	cObjectListIt lpIterator = mObjects.begin();
	while ( lpIterator != mObjects.end()  )
	{
		 // si tenemos un Objeto con el nombre del Objeto como parametro ...
		 if((* lpIterator)->GetName() == lacName )
		 {
			 cCollisionIt lpCollisionIt = mCollisions.begin();
			 while (lpCollisionIt != mCollisions.end() )
			 {
				 if (lpCollisionIt->lpObject1 == (*lpIterator))
				{
						 lpCollisionIt = mCollisions.erase(lpCollisionIt);
				}
				 else
				{
				 ++lpCollisionIt;
				}
			 }

			 delete (* lpIterator); //Borramos el OBJETO
			 
			 // y luego lo eliminamos de la lista
			 lpIterator = mObjects.erase(lpIterator); // Borrar el PUNTERO al objeto
			
			 return;			
		 }
		 else
		 {
			 lpIterator++; // Sino continuamos recorriendo la lista
		 }
	}	
}

void cLevel::Spawn(float luiX,float luiY, std::string lacName ){// Here we creates new shoots objects
	
		if ( lacName == "PlayerShoot" )
			{
				cObject * lpObject = new cShoot( (unsigned)luiX, ((unsigned)luiY -1 ),lacName , -15.0f ,'\xb3');
				mObjects.push_back(lpObject);// Creamos un disparo desde la posición de la nave '\x18''\xba'
			}
	 	else if (lacName == "AlienShoot" )
			{
				cObject * lpObject = new cShoot( (unsigned)luiX, ((unsigned)luiY +1 ),lacName , +15.0f ,'\x19');
				mObjects.push_back(lpObject);// Creamos un disparo desde la posición de la nave '\x18''\xba'
			}	
		else if (lacName == "Player")
			{
				cObject * lpObject = new cPlayer( (unsigned)luiX, ((unsigned)luiY +1 ), lacName, '+');
				mObjects.push_back(lpObject);
			}
}


void cLevel::Update(float lfTimestep)
{
	mCollisions.resize(0);
	
	for (cObjectListIt lpIterator1 = mObjects.begin(); lpIterator1 !=  mObjects.end() ; ++lpIterator1 )
	{ 
		(*lpIterator1)->Update(lfTimestep); //Aqui actualizamos Objetos varios

		//Recorremos la lista de Celdas Especiales...
		for (cSpecialCellDictionaryIt lpCellIterator = mDictionary.begin(); lpCellIterator != mDictionary.end(); lpCellIterator++)
		{
			// si la posición de este objeto (Param2) coincide con la de la Speciall Cell (además de ser esta una SpecialLocation) 
				if( ( lpCellIterator->meCellContent == eSpecialLocation ) &&
					( (unsigned)(*lpIterator1)->GetX() == lpCellIterator->miX ) &&
					 ( (unsigned)(*lpIterator1)->GetY() == lpCellIterator->miY ) )
				{
					cCollision lCollision;
					lCollision.lpObject1 = (*lpIterator1);
					lCollision.lpSpecialCell = &(*lpCellIterator);
					mCollisions.push_back(lCollision);
				//	OutputDebugString("Collision Detected \n");
				// tenemos una colision y guardamos en una lista la colision con los 2 objetos respectivos
				}
		}	
	}
	 mLevelRules.EvalRules(); 
	
	 
}

void cLevel::Render()
{
	// Get the graphic manager
	cGraphicManager & lGraphic = cGraphicManager::Get();

	for (unsigned luiIndex = 0 ; luiIndex != muiArea ; luiIndex++)
		{			
			lGraphic.SetColor(eLightBlue, eBlack);
				
			if(mabMap[luiIndex] != 1)
				lGraphic.WriteChar(luiIndex , 0 , '\xb0'); // Mostramos Rectangulillos
		}
		
	for (cSpecialCellDictionaryIt lpIterator = mDictionary.begin(); lpIterator != mDictionary.end(); lpIterator++)
		{
			if (lpIterator->meCellContent == eSpecialLocation) // If the Content of the cell it´s a Special Location print something 
					{
					lGraphic.SetColor(eLightPurple, eBlack);
					lGraphic.WriteChar(lpIterator->miX , lpIterator->miY , lpIterator->mcSymbol);// Recorriendo y Renderizando las SpecialCells
					
#ifndef DEBUG
						if (lpIterator->mcSymbol == ')')
						{
								cGraphicManager::Get().WriteChar( (unsigned)lpIterator->miX, (unsigned)(lpIterator->miY- 3), '\xb0');

								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -1), (unsigned)(lpIterator->miY - 2), '\xb0');
								cGraphicManager::Get().WriteChar( (unsigned)lpIterator->miX, (unsigned)(lpIterator->miY - 2), '\xb1');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +1), (unsigned)(lpIterator->miY - 2), '\xb0');

								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -2), (unsigned)(lpIterator->miY- 1), '\xb0');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -1), (unsigned)(lpIterator->miY - 1), '\xb1');
								cGraphicManager::Get().WriteChar( (unsigned)lpIterator->miX, (unsigned)(lpIterator->miY - 1), '\xb2');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +1), (unsigned)(lpIterator->miY- 1), '\xb1');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +2), (unsigned)(lpIterator->miY- 1), '\xb0');

								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -3), (unsigned)lpIterator->miY, '\xb0');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -2), (unsigned)lpIterator->miY, '\xb1');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -1), (unsigned)lpIterator->miY, '\xb2');
								cGraphicManager::Get().WriteChar((unsigned) lpIterator->miX,(unsigned) lpIterator->miY, '\xdb');// Hit Here to kill !
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +1),(unsigned) lpIterator->miY, '\xb2');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +2),(unsigned) lpIterator->miY, '\xb1');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +3),(unsigned) lpIterator->miY, '\xb0');
 
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -2),(unsigned) (lpIterator->miY + 1), '\xb0');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -1), (unsigned)(lpIterator->miY + 1), '\xb1');
								cGraphicManager::Get().WriteChar((unsigned) lpIterator->miX, (lpIterator->miY + 1), '\xb2');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +1),(unsigned) (lpIterator->miY + 1), '\xb1');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +2),(unsigned) (lpIterator->miY + 1), '\xb0' );

								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX -1), (unsigned)(lpIterator->miY + 2), '\xb0');
								cGraphicManager::Get().WriteChar( (unsigned)lpIterator->miX, (unsigned)(lpIterator->miY + 2), '\xb1');
								cGraphicManager::Get().WriteChar( (unsigned)(lpIterator->miX +1), (unsigned)(lpIterator->miY+ 2), '\xb0');

								cGraphicManager::Get().WriteChar( (unsigned)lpIterator->miX, (unsigned)(lpIterator->miY + 3), '\xb0');
						}
#endif
					}						
		}

			for (cObjectListIt lpIterator = mObjects.begin(); lpIterator != mObjects.end(); ++lpIterator)
			{
				(*lpIterator)->Render();// Recorremos la lista y Renderizamos cada objeto
			}			
					
}
void cLevel::RemoveAllInCollision()
{

		for (cCollisionIt lpIterator = mRemoveList.begin(); lpIterator !=  mRemoveList.end() ; ++lpIterator )
	{
		// si hay un puntero a objeto adonde apunta lpIterator
		
		delete  lpIterator->lpObject1;// los eliminamos, (:D  
	} 

	mRemoveList.clear();// limpiando el listado de punteros en la lista

}


bool cLevel::DeInit()
{

	for (cObjectListIt lpIterator = mObjects.begin(); lpIterator !=  mObjects.end() ; ++lpIterator )
	{
		// si hay un puntero a objeto adonde apunta lpIterator
			delete * lpIterator;// los eliminamos, (:D  
	} 

//	mCollisions.resize(0);

	mObjects.clear();// limpiando el listado de punteros en la lista

	mDictionary.clear(); 

	mLevelRules.DeInit();

	delete [] mabMap;// eso sería todo supongo..

	return true;
}