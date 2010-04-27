#include "GraphicManager.h"


void cGraphicManager::Init()
	{
		// Initializing the Handle
		mHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		// Initializing the Backbuffer
		memset(macBackBuffer,' ',kuiConsoleArea);

		ShowTheCursor(false); // apagar el cursor

		//Initializing the color buffer to black and white
		memset(macColorBuffer, 0x0F,kuiConsoleArea);
	}

void cGraphicManager::Deinit()
	{
		ShowTheCursor(true);
	}

void cGraphicManager::ShowTheCursor(bool lbShow) // Mostrar/Ocultar el Cursor
{
	CONSOLE_CURSOR_INFO lCursor;
	if (GetConsoleCursorInfo(mHandle, &lCursor))
	{
		lCursor.bVisible = lbShow;
		SetConsoleCursorInfo(mHandle, &lCursor);
	}
}


void cGraphicManager::SwapBuffer()
	{
		//Initializate the coordinates
		COORD lCoord = {0, 0};
		//Set the position
		SetConsoleCursorPosition(mHandle, lCoord);

		//Lock the console
		LockWindowUpdate(GetConsoleWindow());

		// Prepare the vars
		unsigned luiStart = 0;
		unsigned char lcColor = macColorBuffer[0];

		//For each Characters in the Buffers
		for (unsigned luiIndex = 1; luiIndex < kuiConsoleArea; ++luiIndex)
		{
			// If the color changed
			if (macColorBuffer[luiIndex] != lcColor){

				//Set the color
			SetConsoleTextAttribute(mHandle, (WORD)lcColor);

			//Print the Characters
			DWORD liCount;
			int liCharacterCount = luiIndex - luiStart;
			WriteConsole(mHandle, &(macBackBuffer[luiStart]),
				liCharacterCount, &liCount, NULL);
			//Update Information
			luiStart = luiIndex;
			lcColor = macColorBuffer[ luiIndex];
			}
		}
		//Set the color
		SetConsoleTextAttribute(mHandle, (WORD)lcColor);

		//Print the last chunk
		DWORD liCount;
		int liCharacterCount = kuiConsoleArea - luiStart;
		WriteConsole(mHandle, &(macBackBuffer[luiStart]),
			liCharacterCount, &liCount, NULL);

		//Set the position
		SetConsoleCursorPosition(mHandle,lCoord);

		//UnLock the console
		LockWindowUpdate(NULL);
}

void cGraphicManager::ClearBuffer()
{
	memset(macBackBuffer, ' ', kuiConsoleArea);
	memset(macColorBuffer, mcCurrentColor, kuiConsoleArea);
}

void cGraphicManager::WriteChar( unsigned luiX, unsigned luiY, char lChar )
	{
		unsigned luiIndex =  luiX + luiY * kuiConsoleDimX; 
		macBackBuffer[luiIndex] = lChar; // asigna un char al indicie con nuestras coordenadas
		macColorBuffer[luiIndex] = mcCurrentColor ;
		
	}

void cGraphicManager::WriteChars( unsigned int luiX, unsigned int luiY,const char * lacStr, unsigned int luiLen)
	{
		unsigned luiIndex =  luiX + luiY * kuiConsoleDimX; //inicia un indice con nuestras coordenadas
		assert( luiIndex + luiLen < kuiConsoleArea ); // controla que la cadena no séa más grande que el area de la consola

		memcpy(&(macBackBuffer[luiIndex]), lacStr, luiLen);// copia en la memoria del BackBuffer la cadena en su lugar
		memset(&(macColorBuffer[luiIndex]), mcCurrentColor, luiLen);
	}

void cGraphicManager::WriteChars(unsigned int luiX, unsigned int luiY,const char *lacStr)
	{
		WriteChars(luiX, luiY, lacStr, strlen(lacStr) ); // determina la longitud de la cadena y la pasa al metodo sobrecargado para terminar
	}

void cGraphicManager::SetColor(eColor leFore, eColor leBack)
	{
		unsigned char lcForeColor = (unsigned char)leFore;
		unsigned char lcBackColor = (unsigned char)leBack;
		lcBackColor <<= 4; 

		mcCurrentColor = (lcForeColor | lcBackColor);
	}

void cGraphicManager::SetForegroundColor(eColor leColor)
	{
		//make 0 the old ForeColor
		unsigned char lcBackColor = (mcCurrentColor & 0xF0);
		unsigned char lcForeColor = (unsigned char) leColor ;
			
		mcCurrentColor = (lcBackColor |lcForeColor); 
}


void cGraphicManager::SetBackgroundColor( eColor leColor)
	{
	// Displace the color back color to the right position
		unsigned char lcBackColor = (unsigned char)leColor << 4;
   // Make 0 the old background color
		unsigned char lcForeColor = (mcCurrentColor & 0x0F);
		mcCurrentColor = (lcBackColor|lcForeColor);
		
	}
