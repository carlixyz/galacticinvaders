#include <stdio.h>
#include <stdlib.h>
#include "Keyboard.h"

//constante usada en el metodo Check()
const static unsigned kuiInputBufferSize = 128;


void cKeyboard::KeyEventProc(KEY_EVENT_RECORD lKey){
	if (lKey.wVirtualKeyCode >= 0 && lKey.wVirtualKeyCode < kuiInputChanelSize)
	{
		mabInputBuffer[ lKey.wVirtualKeyCode ] = (lKey.bKeyDown == TRUE);
	}
}

void cKeyboard::Init(){
// Get the standard input handle
	mStdin = GetStdHandle(STD_INPUT_HANDLE);
// Inicialization 
	memset(mabInputBuffer, 0, kuiInputChanelSize);

	if (mStdin == INVALID_HANDLE_VALUE)
	{
		printf("Error: GetStdHandle\n");
		return;
	}

//Save the current input mode, to be restored on exit.
	if (!GetConsoleMode(mStdin, &mOldModeSaved))
	{
		printf("Error: GetConsoleMode\n");
		return;
	}

// Enable the window input events.
	DWORD lNewMode = ENABLE_WINDOW_INPUT;
	if (!SetConsoleMode(mStdin, lNewMode))
	{
		printf("Error: SetConsoleMode\n");
		return;
	}
	mbIsValid = true;
}


void cKeyboard::Deinit(){
	if (!SetConsoleMode(mStdin, mOldModeSaved) )
		printf("Error: SetConsoleMode\n");

	mbIsValid = false;
	}

void cKeyboard::Update(){

	INPUT_RECORD laInBuf[kuiInputBufferSize];
	DWORD luiNumRead;

	// Check if there are events
	if (!PeekConsoleInput( mStdin,				// input buffer handle
						  laInBuf,				// buffer to read into
						  kuiInputBufferSize,	// size of read buffer
						  &luiNumRead) )		// number of records read
	{
		printf("Error: PeekConsoleInput\n");
		return;
	}
	if ( luiNumRead <= 0 ){
		return;
	}

	// Read the events and clear the buffer
	if ( !ReadConsoleInput(mStdin,				// input buffer handle
						  laInBuf,				// buffer to read into
						  kuiInputBufferSize,	// size of read buffer
						  &luiNumRead) )		// number of records read
	{
		printf("Error: ReadConsoleInput\n");
		return;
	}
	// Dispatch the events to the apropiate handler
	for (unsigned luiIndex = 0; luiIndex < luiNumRead; luiIndex++){
		// Keyboard input
		if (laInBuf[luiIndex].EventType == KEY_EVENT){
			KeyEventProc(laInBuf[luiIndex].Event.KeyEvent);
		}
	}

}



float cKeyboard::Check(unsigned int luiEntry){
	if (mabInputBuffer[luiEntry]){
		return 1.0f;
	}
	return 0.0f;
}

bool cKeyboard::IsValid(){
	return mbIsValid;
}