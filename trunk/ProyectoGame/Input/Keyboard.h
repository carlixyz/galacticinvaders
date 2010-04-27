#pragma once
#include "GenericDevice.h"
#include <Windows.h>

class cKeyboard : public cGenericDevice
{
	HANDLE mStdin;
	DWORD mOldModeSaved;
	static const unsigned kuiInputChanelSize = 256;
	bool mabInputBuffer[kuiInputChanelSize];
	bool mbIsValid;
	void KeyEventProc(KEY_EVENT_RECORD lKey);

	public:
		// Constructor
	inline cKeyboard(){mbIsValid = false;}

	void Init();
	void Deinit(void);
	void Update(void);
	float Check(unsigned luiEntry);
	bool IsValid(void);
	
};