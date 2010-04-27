#pragma once

#include "..\Utility\singleton.h"
#define _WIN32_WINNT 0x0500	//el compilador llora por GetConsoleWindow al compilar y hay que darle de comer esto....
#include <Windows.h> // Wincon.h pide estas lineas para declarar GetConsoleWindow... caprichos
#include <string.h> 
#include <assert.h>
//#include <Wincon.h> // se pueden destacar un par de opciones como CONSOLEFULLSCREEN y FULLSCREENHARDWARE donde la consola controla el hard, interesante...

// Color definition
enum eColor{
	eBlack = 0,
	eBlue,
	eGreen,
	eAqua,
	eRed,
	ePurple,
	eYellow,
	eWhite,
	eGray,
	eLightBlue,
	eLightGreen,
	eLightAqua,
	eLightRed,
	eLightPurple,
	eLightYellow,
	eLightWhite
};


class cGraphicManager : public cSingleton<cGraphicManager> // Administrador de Graficos, muy grafico
{
	friend class cSingleton<cGraphicManager>;
	static const unsigned kuiConsoleDimX = 80; // dimensiones de la consola
	static const unsigned kuiConsoleDimY = 25; // ojo: solo es posible Inicializar así const statics y enums
	static const unsigned kuiConsoleArea = kuiConsoleDimX * kuiConsoleDimY; // area = ancho * alto

	char macBackBuffer[ kuiConsoleArea ]; //Buffer con la información del area de pantalla
	unsigned char mcCurrentColor; // Color Actual
	unsigned char macColorBuffer[ kuiConsoleArea ];// Buffer con información de color
	
	HANDLE mHandle;

	void ShowTheCursor(bool lbShow);// mostrar el cursor true o false

	void WriteChars( unsigned luiX, unsigned luiY, const char * lacStr, unsigned luiLen); // metodo priv. sobrecargado para servír a WriteChars

protected:
	cGraphicManager(){;} // Constructor protegido
public:
	void Init();
	void Deinit();

	void WriteChar( unsigned luiX, unsigned luiY, char lChar );// Asigna 1 char a una ubicación	
	void WriteChars( unsigned luiX, unsigned luiY,const char * lacStr);// para asignar más de 1 char
	
	void SwapBuffer();
	void ClearBuffer();

	void SetColor( eColor leFore, eColor leBack);// determina color frontal y de fondo
	void SetForegroundColor(eColor leColor);
	void SetBackgroundColor( eColor leColor);
	

	
};
