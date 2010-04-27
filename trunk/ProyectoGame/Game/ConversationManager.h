
#pragma once
#include "..\Utility\singleton.h"
#include <vector>
#include <list>
#include <tinystr.h>
#include <tinyxml.h>
#include <Windows.h> 
using namespace std;

enum eConversationNodeType //tipo de conversación
{
	eNormalTalk,
	eChooseTalk,
	eEndConversation
};

struct cCharacterSpeaker // Personajes que Hablan
{
	int miCharacterId;
	string macCharacterName;
};

struct cConversationNode // SubNodos de la conversación
{
	eConversationNodeType meType;
	string macText;
	float mfDuration;
	int miCharacterId;

	typedef std::vector<cConversationNode> cConversationChildren;
	cConversationChildren mChildren;
	// mChildren
};


struct cConversation // Raíz del arbol de subconversaciones, en nuestro ejemplo tenemos una sola
{
	string  macName;
	cConversationNode mRoot;
};

class cConversationManager : public cSingleton<cConversationManager> // Administrador de Graficos, muy grafico
{
	friend class cSingleton<cConversationManager>;

	typedef std::vector<cCharacterSpeaker> cSpeakersCharacters;//  Vector de personajes que hablan

	typedef std::list<cConversation> cConversationsList; //  Lista de conversaciones
	typedef cConversationsList::iterator cConversationIt ;// Iterador

	cSpeakersCharacters mSpeakers;// Declaration of "characters who speaks" (not the sound system)
	
	cConversationsList mConversations; //declaracion lista de conversaciones ( una sola en este caso)
	
	cConversationNode * mpCurrentConversationNode; //declaración puntero a nodo actual de la conversación 

	bool BecomePressed(const int &lActionId);

	bool mbConversationState;

	float mfMessageTime;
	unsigned muiChooseOption;// Actual choice

	public:

		void Init( const string &lacConversationFile );
		void DeInit( void) ;

		void ParseConversation( TiXmlElement* pElem );
		void ParseNode( TiXmlElement *lpElem, cConversationNode *lpCurrentNode );
		void NextMessage( unsigned luiNextMessageIndex );

		void Update( float lfTimestep );
		void Render();

		void StartConversation( const string &lacConversationId ); // con esto llamamos al Conversation Manager desde Statement.cpp
		bool &IsInConversation(){return mbConversationState ;} //Eval Is in conversation
};