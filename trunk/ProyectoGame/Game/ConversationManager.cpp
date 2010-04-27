#include "ConversationManager.h"
#include "..\Input\InputManager.h"
#include "..\Graphics\GraphicManager.h"


void cConversationManager::Init(const string &lacConversationFile)
{
	TiXmlDocument doc(lacConversationFile);
	bool lbLoadOk = doc.LoadFile();
	if ( lbLoadOk )
	{
	
		TiXmlHandle lpRoot( &doc ); // Buscamos el Handle del Documento
		TiXmlElement *lpElem; 
	//	TiXmlAttribute* pAttrib; // Con estos punteros accedemos Elementos y Atributos
		lpRoot = lpRoot.FirstChildElement().Element(); //Nos posicionamos en la etiqueta "Conversations"

	// Read all the Characters (los Personajes,no los Chars)
		lpElem = lpRoot.FirstChild( "Characters" ).FirstChild().Element();
		for (lpElem; lpElem; lpElem = lpElem->NextSiblingElement())
		{			
			cCharacterSpeaker lCharacter;
			//Character ID
			lpElem->QueryIntAttribute("speakerId", &lCharacter.miCharacterId );
			assert(lCharacter.miCharacterId >= 0);

			// Character Name
			const char * lacName = lpElem->GetText();

			assert(lacName);
			lCharacter.macCharacterName = lacName;

			// Add the character to the Vector
			mSpeakers.push_back( lCharacter );
		}

	// Read all the conversations 
		lpElem = lpRoot.FirstChild( "Conversation" ).Element();
		for( lpElem; lpElem; lpElem = lpElem->NextSiblingElement("Conversation"))
		{			
			ParseConversation( lpElem );
		}

	}
}

void cConversationManager::ParseConversation(TiXmlElement *pElem)
{
	cConversation lConversation;

	// Read the conversation ID
	const char * lacNameId = pElem->Attribute("nameId");
	assert(lacNameId);
	lConversation.macName = lacNameId;// guardando el nombre de la conversación

	// Read the tree
	ParseNode( pElem->FirstChildElement(), &lConversation.mRoot );// guardando la ruta de la conversación

	// Add the conversations to the list
	mConversations.push_back(lConversation);// guardando en la lista la conversación
}

void cConversationManager::ParseNode( TiXmlElement *lpElem, cConversationNode *lpCurrentNode )
{	
	//Check the stop condition
	if ( lpElem == NULL )
	{
		lpCurrentNode->meType = eEndConversation;
		return;
	}
	// Get the type of the XML element
	string lacTag = lpElem->ValueStr();
	if ( lacTag == "Talk" )
	{
		// Set the type
		lpCurrentNode->meType = eNormalTalk;

		// Read the text
		const char * lacText = lpElem->GetText();
		assert(lacText);
		lpCurrentNode->macText = lacText;

		// Read the speaker Id
		lpElem->QueryIntAttribute("speakerId", &(lpCurrentNode->miCharacterId) );
		assert(lpCurrentNode->miCharacterId >= 0);
		assert(lpCurrentNode->miCharacterId < (int)mSpeakers.size() );

		// Read the time
		lpElem->QueryFloatAttribute("time", &(lpCurrentNode->mfDuration) );

		//Prepare the next node
		cConversationNode lNode;
		lpCurrentNode->mChildren.push_back( lNode ); // Asignando un puntero del Nodo a la lista 

		// Continue the recursivity
		ParseNode( lpElem->NextSiblingElement(), &(lpCurrentNode->mChildren[0]) );
	}
	else if ( lacTag == "ChooseTalk" )
	{
		// Set the type
		lpCurrentNode->meType = eChooseTalk;

		// Read all the options
		TiXmlElement *pElem2 = lpElem->FirstChildElement();
		for (pElem2; pElem2; pElem2 = pElem2->NextSiblingElement())
		{
			assert(pElem2);
			assert( pElem2->ValueStr() == "Option" );

			//Add a node to the vector
			cConversationNode lNode;
			lpCurrentNode->mChildren.push_back( lNode ); 

			// Continue the recursivity
			unsigned luiLastIndex = lpCurrentNode->mChildren.size() - 1;  // 
			ParseNode( pElem2->FirstChildElement(), &(lpCurrentNode->mChildren[ luiLastIndex ]) );
		}
	}else
		assert(0 && "Wrong tag\n");

}

void cConversationManager::NextMessage(unsigned int luiNextMessageIndex)
{
	// Checks to make sure that all is right
	assert( mpCurrentConversationNode );
	assert( luiNextMessageIndex < mpCurrentConversationNode->mChildren.size() );

	// Select the next node
	bool lbIsChooseNode = (mpCurrentConversationNode->meType == eChooseTalk );
	mpCurrentConversationNode = &(mpCurrentConversationNode->mChildren[ luiNextMessageIndex ]);

	// If the conversation have finished 
	if ( mpCurrentConversationNode->meType == eEndConversation )
	{
		mpCurrentConversationNode = NULL;
	}
	else if ( lbIsChooseNode )
	{
		// This node is the option text
		// We need to choose the next child	NextMessage(0);
		NextMessage(0);
	}
	else
	{
		//Set the right values
		muiChooseOption = 0;
		mfMessageTime = mpCurrentConversationNode->mfDuration;
	/*	this->mbConversationState = false;
		OutputDebugString( "NextMessage: setting mbConversation in false" );*/
	}
}

void cConversationManager::StartConversation(const std::string &lacConversationId)
{
	mbConversationState = true; // si asignamos true, suspendemos el Movimiento de Player
	
	for( cConversationIt lpIterator = mConversations.begin(); lpIterator != mConversations.end(); lpIterator++ )
	{	

		if (lpIterator->macName == lacConversationId ){// si tenemos una conversación con el nombre de lacConversationId...
			
			mpCurrentConversationNode = &lpIterator->mRoot; // Asignamos con el '&' (Address) del root a nuestro puntero de acceso
			
			mfMessageTime = mpCurrentConversationNode->mfDuration; // Asignamos el tipo inicial
			
			muiChooseOption = 0;

		}
	}
}

bool cConversationManager::BecomePressed(const int &lActionId)
{
	const cInputAction & lAction = cInputManager::Get().GetAction( lActionId );
	return ( lAction.GetBecomePressed() ); // return true if the current action was pressed
}

void cConversationManager::Update(float lfTimestep)
{
//	if(BecomePressed( eIA_Accept )){OutputDebugString( "\n PRESSING ENTER KEY ");  }

	if (mbConversationState && mpCurrentConversationNode != NULL)
	{
	switch (mpCurrentConversationNode->meType)
		{
			case 0:
				{// Enum 0; Nodo activo de tipo eNormalTalk
					// Decrease the message time
					mfMessageTime -= lfTimestep;
					
					if ( mfMessageTime <= 0.0f || BecomePressed( eIA_Shoot ) )
					{
						//Need to continue with the next message or node
						NextMessage(0);
					}
				}
			break;
			
			case 1:
				{// Enum 1; Nodo activo de tipo eChooseTalk

					if( BecomePressed( eIA_GoUp ) && ( muiChooseOption > 0 )  )
						 muiChooseOption--;
					
					if( BecomePressed( eIA_GoDown ) && ( muiChooseOption < (mpCurrentConversationNode->mChildren.size() -1 )) )
						muiChooseOption++;
								
					if ( BecomePressed( eIA_Shoot ) )
					{
						NextMessage( muiChooseOption );
					}
				}
			break;

			default:
				{// Enum 2; Nodo activo de tipo eEndConversation
					mpCurrentConversationNode = NULL ;
				}
			break;

		}
	}else
		this->mbConversationState = false; // If we have a null mpCurrentConversationNode then it´s the end
}

void cConversationManager::Render()
{

	if (mbConversationState && mpCurrentConversationNode != NULL )// Si Hay Conversación y el nodo no es NULL
	{
	cGraphicManager::Get().SetColor(eLightGreen, eBlack);// Don´t get Horrorized about this !!! it´s just the Dialog Window Frame XP
	cGraphicManager::Get().WriteChars( 4, 6, "\xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf" );
	cGraphicManager::Get().WriteChars( 4, 7, "\xb3                                                                      \xb3" );
	cGraphicManager::Get().WriteChars( 4, 8, "\xc3\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xb4" );
	cGraphicManager::Get().WriteChars( 4, 9, "\xb3                                                                      \xb3" );
	cGraphicManager::Get().WriteChars( 4, 10, "\xb3                                                                      \xb3" );
	cGraphicManager::Get().WriteChars( 4, 11, "\xb3                                                                      \xb3" );
	cGraphicManager::Get().WriteChars( 4, 12, "\xb3                                                                      \xb3" );
	cGraphicManager::Get().WriteChars( 4, 13, "\xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9" ); 
	cGraphicManager::Get().SetColor(eWhite, eBlack);
		
		switch ( mpCurrentConversationNode->meType)
		{
			case 0:
				{// Enum 0; Nodo activo de tipo eNormalTalk
						
				for (int liSpeakersId = 0; liSpeakersId < (int)mSpeakers.size(); ++liSpeakersId)
					{ 
						if (mSpeakers[liSpeakersId].miCharacterId == mpCurrentConversationNode->miCharacterId)
							cGraphicManager::Get().WriteChars( 6, 7, mSpeakers[liSpeakersId].macCharacterName.c_str() );
					}	// Check If the character Id it´s the same as the Speakers Id and Show who is Speaking...
							
					cGraphicManager::Get().WriteChars( 6, 9, mpCurrentConversationNode->macText.c_str() );// Character Speak
				}
			break;
			
			case 1:
				{// Enum 1; Nodo activo de tipo eChooseTalk

					cConversationNode * lcpChoice  = &( mpCurrentConversationNode->mChildren[ muiChooseOption ]);// Choosen option

					for (int liSpeakersId = 0; liSpeakersId < (int)mSpeakers.size(); ++liSpeakersId)
						{
							if (mSpeakers[liSpeakersId].miCharacterId == lcpChoice->miCharacterId)
								cGraphicManager::Get().WriteChars( 6, 7, mSpeakers[liSpeakersId].macCharacterName.c_str() );
						}	// Check If the character Id it´s the same as the Speakers Id and Show who is Asking...

					for (unsigned liOptionIndex = 0; liOptionIndex < (mpCurrentConversationNode->mChildren.size() ); liOptionIndex++ )
					{
						cConversationNode * lcpOptions  = &( mpCurrentConversationNode->mChildren[ liOptionIndex ]);//Show posible options

						if( lcpOptions != lcpChoice)// Printing the unselected Options
						{
						cGraphicManager::Get().SetColor(eGray, eBlack);// Color de las opciones
						cGraphicManager::Get().WriteChars( 6, (9 + liOptionIndex), lcpOptions->macText.c_str() );
						}
						else
							if( lcpOptions == lcpChoice) // Printing the Choice
							{
								cGraphicManager::Get().SetColor(eLightWhite, eBlack);// Color de la Respuesta elegida
								cGraphicManager::Get().WriteChars( 6, (9 + liOptionIndex), lcpChoice->macText.c_str() );
							}
					}
				}
			break;
		}
	}
}


void cConversationManager::DeInit()
{
	mConversations.clear();

	mSpeakers.resize(0);

}