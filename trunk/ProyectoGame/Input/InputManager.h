#pragma once

#include <vector>

#include "..\Utility\singleton.h"
#include "..\Input\Keyboard.h"
#include "..\Input\InputAction.h"
#include "..\Input\InputEntry.h"
#include "..\Game\InputConfiguration.h"


enum eDevices
{
	eKeyboard = 0
};

class cInputManager : public cSingleton<cInputManager> // otra clase Singleton, a weird huge one...
{
	friend class cSingleton<cInputManager>;		
	float Check(int liDevice, int liChannel); // metodo privado para comprobar el estado "true" del dispositivo

	std::vector<cInputAction> mActions;			// vector de InputActions..
	std::vector<cGenericDevice *> mDevices;		// un vector puntero a Generic Device
	std::vector< std::vector< cInputEntry > > mMapped; //un vector de vectores del tipo InputEntry, ni mas ni menos

	public:		
		void Init( const tActionMapping laActionMapping[], unsigned luiActionCount );
		void Update(const float &lfTimestep);
		inline cInputAction &GetAction(const int &lActionId) { return mActions[lActionId]; }
		void Deinit(void);
};

